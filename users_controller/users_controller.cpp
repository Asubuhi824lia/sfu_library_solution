#include "users_controller.h"

#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDataStream>

users_controller::users_controller(QObject *parent) : QObject(parent) {
    QString dir_name = "./admins";
    extract_data_from_files(dir_name, this->admins);
    QDir directory(dir_name);
    if(directory.exists()) {
        QStringList	items_list =  directory.entryList((QStringList() << "*.txt"),QDir::Files);
        if (items_list.isEmpty()) {
            user_info admin;
            admin.login = "admin";
            admin.password = "admin";
            add_admin(admin);
        }
    }

    dir_name = "./librarians";
    extract_data_from_files(dir_name, this->librarians);

    dir_name = "./readers";
    extract_data_from_files(dir_name, this->readers);
}

void users_controller::extract_data_from_files (QString& dir_name, QMap<user_info, QString>& users) {
    QDir directory(dir_name);
    if(directory.exists()) {
        QStringList	items_list =  directory.entryList((QStringList() << "*.txt"),QDir::Files);
        for(QString& item : items_list) {
            QFile file(tr("%1/%2").arg(dir_name).arg(item));

            if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
                user_info reader = filling_fields(file);

                add_user_to_map(reader, tr("%1/%2").arg(dir_name).arg(item), users);
            } else {
                exit(EACCES);
            }
        }
    } else {
        bool state = directory.mkpath(".");
        if(state) {
            create_number(dir_name);
        } else {
            exit(EACCES);
        }
    }
}

QString users_controller::remove_endl (const QByteArray& s) {
    QString str = s;
    return str.replace("\n", "").replace("\r", "");
}

user_info users_controller::filling_fields(QFile& file) {
    user_info user;
    user.login = this->remove_endl(file.readLine());
    user.password = this->remove_endl(file.readLine());
    user.name = this->remove_endl(file.readLine());
    user.surname = this->remove_endl(file.readLine());
    user.middle_name = this->remove_endl(file.readLine());
    user.num_library_card = this->remove_endl(file.readLine());
    user.home_address = this->remove_endl(file.readLine());

    return user;
}

bool users_controller::add_librarian(const user_info& librarian) {
    if (user_is_present(librarian.login)) {
        return false;
    }

    add_user_to_map(librarian, tr("./librarians/user%1.txt").arg(get_number("./librarians")), this->librarians);
    add_user_to_file(librarian, tr("./librarians"));
    inc_number("./librarians");
    return true;
}

bool users_controller::remove_librarian(const user_info& librarian) {
    for( QMap<user_info, QString>::iterator it = this->librarians.begin(); it != this->librarians.end(); ) {
        user_info item = it.key();
        if(item == librarian) {
            QString file_name = it.value();
            this->librarians.erase(it);

            if(!QFile::remove(file_name)) {
                exit(EACCES);
            }

            return true;
        } else {
            ++it;
        }
    }
    return false;
}

bool users_controller::remove_librarian(QString login) {
    for( QMap<user_info, QString>::iterator it = this->librarians.begin(); it != this->librarians.end(); ) {
        user_info item = it.key();
        if(item.login == login) {
            QString file_name = it.value();
            this->librarians.erase(it);

            if(!QFile::remove(file_name)) {
                exit(EACCES);
            }

            return true;
        } else {
            ++it;
        }
    }
    return false;
}

int users_controller::get_num_librarians () {
    return librarians.size();
}

bool users_controller::add_reader(const user_info& user) {
    if (user_is_present(user.login)) {
        return false;
    }

    add_user_to_map(user, tr("./readers/user%1.txt").arg(get_number("./readers")), this->readers);
    add_user_to_file(user, tr("./readers"));
    inc_number("./readers");
    return true;
}

bool users_controller::remove_reader(const user_info& reader) {
    for( QMap<user_info, QString>::iterator it = this->readers.begin(); it != this->readers.end(); ) {
        user_info item = it.key();
        if(item == reader) {
            QString file_name = it.value();
            this->readers.erase(it);

            if(!QFile::remove(file_name)) {
                exit(EACCES);
            }

            return true;
        } else {
            ++it;
        }
    }
    return false;
}

bool users_controller::remove_reader(QString login) {
    for( QMap<user_info, QString>::iterator it = this->readers.begin(); it != this->readers.end(); ) {
        user_info item = it.key();
        if(item.login == login) {
            QString file_name = it.value();
            this->readers.erase(it);

            if(!QFile::remove(file_name)) {
                exit(EACCES);
            }

            return true;
        } else {
            ++it;
        }
    }
    return false;
}

int users_controller::get_num_readers () {
    return readers.size();
}

QStringList users_controller::get_list_librarians () {
    return this->get_list_users(this->librarians);
}
QStringList users_controller::get_list_readers () {
    return this->get_list_users(this->readers);
}

bool users_controller::check_users_login(QString login) {
    return (check_admin_login(login) || check_librarian_login(login) || check_reader_login(login));
}

bool users_controller::check_admin_login(QString login) {
    auto s = get_admin(login);
    return (!s.login.isEmpty());
}
bool users_controller::check_librarian_login(QString login) {
    auto s = get_librarian(login);
    return (!s.login.isEmpty());
}
bool users_controller::check_reader_login(QString login) {
    auto s = get_reader(login);
    return (!s.login.isEmpty());
}

QStringList users_controller::get_list_users (QMap<user_info, QString> users) {
    QStringList list;
    for(QMap<user_info, QString>::iterator it = users.begin(); it != users.end(); ++it) {
        const user_info &item = it.key();
        list << item.login;
    }
    return list;
}

const user_info& users_controller::get_admin (const QString login) {
    return this->get_user(login, this->admins);
}

const user_info& users_controller::get_librarian (const QString login) {
    return this->get_user(login, this->librarians);
}

const user_info& users_controller::get_reader (const QString login) {
    return this->get_user(login, this->readers);
}

const user_info& users_controller::get_user (const QString& login, QMap<user_info, QString>& users) {
    for( QMap<user_info, QString>::iterator it = users.begin(); it != users.end(); ) {
        const user_info &item = it.key();
        if (item.login == login) {
            return item;
        } else {
            ++it;
        }
    }

//    return users.begin().key();
    const user_info* u = new user_info();
    return *u;
}

bool users_controller::user_is_present (const QString &login) {
    if (this->get_admin(login).login == login) {
        return true;
    }

    if (this->get_librarian(login).login == login) {
        return true;
    }

    if (this->get_reader(login).login == login) {
        return true;
    }

    return false;
}

bool users_controller::add_admin(const user_info& user) {
    add_user_to_map(user, tr("./admins/user%1.txt").arg(get_number("./admins")), admins);
    add_user_to_file(user, tr("./admins"));
    inc_number("./admins");
    return true;
}

bool users_controller::add_user_to_map (const user_info& user, const QString file_name,
                                        QMap<user_info, QString>& users) {
    users[user] = file_name;
    return true;
}

bool users_controller::add_user_to_file (const user_info& user, const QString file_name) {
    QDir directory(file_name);
    if(directory.exists()) {
        QFile file(tr("%1/user%2.txt").arg(file_name).arg( get_number(file_name) ));
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << user.login << Qt:: endl
                << user.password << Qt:: endl
                << user.name << Qt:: endl
                << user.surname << Qt:: endl
                << user.middle_name << Qt:: endl
                << user.num_library_card << Qt:: endl
                << user.home_address;
            file.close();
        } else {
            exit(EACCES);
        }
        return true;
    } else
        return false;
}

uint64_t users_controller::get_number (const QString& dir_name) {
    QFile file(dir_name + "/.number");
    if(file.open(QIODevice::ReadOnly)) {
        uint64_t num;
        // Проверка на то, нужное ли количество байт считалось
        qint64 read_rv = file.read(reinterpret_cast<char *>(&num), sizeof(num));
        if (read_rv != sizeof(num)) {
            exit(EIO);
        }

        file.close();
        return num;
    } else {
        exit(EACCES);
    }
}

void users_controller::create_number (const QString& dir_name) {
    QFile file(dir_name + "/.number");
    if(file.open(QIODevice::WriteOnly)) {
        uint64_t num = 0;
        file.write(reinterpret_cast<const char *>(&num), sizeof(num));

        file.close();

    } else {
        exit(EACCES);
    }
}

void users_controller::inc_number (const QString& dir_name) {
    QFile file(dir_name + "/.number");
    if(file.open(QIODevice::ReadWrite)) {
        uint64_t num = get_number(dir_name) + 1;
        file.write(reinterpret_cast<const char *>(&num), sizeof(num));

        file.close();
        if (get_number(dir_name) != num) {
            exit(EACCES);
        }
    }
}
