#pragma once

#include "users_controller/users_controller.h"

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class admin_main_window : public QWidget
{
    Q_OBJECT
public:
    explicit admin_main_window(QString login, users_controller& users);

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit home_address;

    QLineEdit login;
    QLineEdit password;

private:
    QListWidget* librarians_list = nullptr;
    QListWidget* readers_list = nullptr;

private:
    QString user;
    users_controller& users_cnr;

private slots:
    void del_librarian_clicked(QListWidgetItem *);
    void add_librarian_clicked();

};
