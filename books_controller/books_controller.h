#pragma once

#include <QMap>
#include <QFile>
#include <QObject>
#include <QString>

struct author_info {
    QString name;
    QString surname;
    QString middle_name;

    bool operator==(const author_info& a) const {
        if((this->name == a.name || this->name == a.name+'\n') &&
           (this->surname == a.surname || this->surname == a.surname+'\n') &&
           (this->middle_name == a.middle_name || this->middle_name == a.middle_name+'\n')) {
            return true;
        } else {
            return false;
        }
    }
};

struct book_info {
    QString book_name;
    QString num_pages;
    QString price;

    author_info auth;

    bool operator<(const book_info& b) const {
        return b.book_name < this->book_name;
    }
};

class books_controller : public QObject {
    Q_OBJECT

private:
    QMap<book_info, QString> books;

public:
    explicit books_controller(QObject *parent = nullptr);

public:
    bool add_item (book_info& book);
    bool remove_item (const author_info& author, const QString& book_name);
    int get_num_items ();
    QVector<book_info> get_books_info ();
    QString remove_endl (QString s);
    bool check_books(book_info& book);

private:
    bool add_item_to_map (book_info& book, QString file_name);
    bool add_item_to_file (book_info& book);

    // Для файла, хранящего значение количества добавленных книг вообще
    uint64_t get_number ();
    void create_number ();
    void inc_number ();

};
