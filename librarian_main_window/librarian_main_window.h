#pragma once

#include "users_controller/users_controller.h"
#include "reg_reader/reg_reader.h"
#include <books_controller/books_controller.h>

#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QListWidgetItem>
#include <QTableWidget>

class librarian_main_window : public QWidget
{
    Q_OBJECT
public:
    explicit librarian_main_window(QString libr_login, users_controller& users, books_controller& books);

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit num_library_card;
    QLineEdit home_address;
    QLineEdit login;
    QLineEdit password;

    QTableWidget tw;
    QListWidget* readers_list = nullptr;

private:
    QString libr_login;
    users_controller& users_cnr;
    books_controller& books_cnr;

private:
    void full_table_books ();

private slots:
    void del_reader_clicked(QListWidgetItem* i);
    void add_reader_clicked();

private slots:
    void accept_book_clicked ();
    void give_out_book_clicked ();

    void add_book_clicked ();
    void write_off_book_clicked ();

};
