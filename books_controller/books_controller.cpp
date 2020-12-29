#include "books_controller.h"

#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDataStream>

books_controller::books_controller(QObject *parent) : QObject(parent) {
    QString dir_name = "./book_info";
    QDir directory(dir_name);
    if(directory.exists()) {
        QStringList	items_list =  directory.entryList((QStringList() << "*.txt"),QDir::Files);
        for(QString& item : items_list) {
            QFile file(tr("%1/%2").arg(dir_name).arg(item));
            if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {

                book_info book;

                // заполнение полей структуры
                book.book_name = file.readLine();
                book.num_pages = file.readLine();
                book.price = file.readLine();
                book.auth.name = file.readLine();
                book.auth.surname = file.readLine();
                book.auth.middle_name = file.readLine();

                add_item_to_map(book, tr("%1/%2").arg(dir_name).arg(item));
            } else {
                exit(EACCES);
            }
        }
    } else {
        bool state = directory.mkpath(".");
        if(state) {
            create_number();
        } else {
            exit(EACCES);
        }
    }
}

bool books_controller::add_item (book_info& book) {
    add_item_to_map(book, tr("./book_info/book%1.txt").arg(get_number()));
    add_item_to_file(book);
    inc_number();
    return true;
}

bool books_controller::remove_item (const author_info& author, const QString& book_name) {
    for( QMap<book_info, QString>::iterator it = books.begin(); it != books.end(); ) {
        book_info item = it.key();
        if((item.auth == author) &&
           (item.book_name == book_name || item.book_name == book_name+'\n')) {
            QString file_name = it.value();
            books.erase(it);

            QFile file(file_name);
            if(file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                file.close();
                file.remove(file_name);
            } else {
                exit(EACCES);
            }
            return true;
        } else {
            ++it;
        }
    }
    return false;
}

int books_controller::get_num_items () {
    return books.size();
}

bool books_controller::add_item_to_map (book_info& book, QString file_name) {
    books[book] = file_name;
    return true;
}

bool books_controller::add_item_to_file (book_info& book) {
    QDir directory("./book_info");
    if(directory.exists()) {
        QFile file(tr("./book_info/book%1.txt").arg( get_number() ));
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << book.book_name << Qt::endl
                << book.num_pages  << Qt::endl
                << book.price << Qt::endl
                << book.auth.name << Qt::endl
                << book.auth.surname << Qt::endl
                << book.auth.middle_name;
            file.close();
        } else {
            exit(EACCES);
        }
        return true;
    } else
        return false;
}

uint64_t books_controller::get_number () {
    QFile file("./book_info/.number");
    if(file.open(QIODevice::ReadOnly)) {
        uint64_t num;
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

void books_controller::create_number () {
    QFile file("./book_info/.number");
    if(file.open(QIODevice::WriteOnly)) {
        uint64_t num = 0;
        file.write(reinterpret_cast<const char *>(&num), sizeof(num));

        file.close();

    } else {
        exit(EACCES);
    }
}

void books_controller::inc_number () {
    QFile file("./book_info/.number");
    if(file.open(QIODevice::ReadWrite)) {
        uint64_t num = get_number() + 1;
        file.write(reinterpret_cast<const char *>(&num), sizeof(num));

        file.close();
        if (get_number() != num) {
            exit(EACCES);
        }
    }
}
