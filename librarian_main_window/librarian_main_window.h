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

private slots:
    void del_reader_clicked(QListWidgetItem* i);
    void add_reader_clicked();

private:
    void full_table_books ();

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit num_library_card;
    QLineEdit home_address;
    QTableWidget tw;
    QLineEdit login;
    QLineEdit password;

    QListWidget* readers_list = nullptr;

private:
    QString libr_login;
    users_controller& users_cnr;
    books_controller& books_cnr;

private slots:
    void accept_book ();
    void give_out_book ();

    void add_book ();
    void write_off_book ();

};
