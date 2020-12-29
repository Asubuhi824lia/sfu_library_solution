#pragma once

#include "users_controller/users_controller.h"
#include "reg_reader/reg_reader.h"
#include <QWidget>
#include <QLineEdit>
#include <QString>
#include <QListWidgetItem>

class librarian_main_window : public QWidget
{
    Q_OBJECT
public:
    explicit librarian_main_window(QString libr_login, users_controller& users);

private slots:
    void del_reader_clicked(QListWidgetItem* i);
    void add_reader_clicked();

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit num_library_card;
    QLineEdit home_address;

    QLineEdit login;
    QLineEdit password;

    QListWidget* readers_list = nullptr;

private:
    QString libr_login;
    users_controller& users_cnr;

};
