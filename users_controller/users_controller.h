#pragma once

#include <QMap>
#include <QFile>
#include <QObject>

struct user_info {
    QString name;
    QString surname;
    QString middle_name;
    QString num_library_card;
    QString home_address;

    QString login;
    QString password;

    bool operator==(const user_info& a) const {
        if (this->login == a.login) {
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const user_info& u) const {
        return u.login < this->login;
    }
};

class users_controller : public QObject {
    Q_OBJECT

public:
    explicit users_controller(QObject *parent = nullptr);

public:
    bool add_admin(const user_info& admin);
    bool add_librarian(const user_info& librarian);
    bool add_reader(const user_info& reader);

    const user_info& get_admin (const QString login);
    const user_info& get_librarian (const QString login);
    const user_info& get_reader (const QString login);

    bool remove_librarian(const user_info& librarian);
    bool remove_librarian(QString login);
    bool remove_reader(const user_info& user);
    bool remove_reader(QString login);

    int get_num_librarians ();
    int get_num_readers ();

    QStringList get_list_librarians ();
    QStringList get_list_readers ();

    bool check_users_login(QString login);

    bool check_admin_login(QString login);
    bool check_librarian_login(QString login);
    bool check_reader_login(QString login);

private:
    QStringList get_list_users (QMap<user_info, QString> users);

private:
    QMap<user_info, QString> admins;
    QMap<user_info, QString> librarians;
    QMap<user_info, QString> readers;

private:
    bool add_user_to_map (const user_info& book, const QString file_name, QMap<user_info, QString>& users);
    bool add_user_to_file (const user_info& book, const QString file_name);

private:
    const user_info& get_user (const QString& login, QMap<user_info, QString>& users);

private:
    user_info filling_fields (QFile& file);

private:
    void extract_data_from_files (QString& dir_name, QMap<user_info, QString>& users);
    QString remove_endl (const QByteArray& s);

private:
    bool user_is_present (const QString &login);


private:
    // dir_name = "./admins"
    // dir_name = "./librarians"
    // dir_name = "./readers"
    uint64_t get_number (const QString& dir_name);
    void create_number (const QString& dir_name);
    void inc_number (const QString& dir_name);

};
