#pragma once

#include "users_controller/users_controller.h"

#include <QWidget>
#include <QLineEdit>

class librarian_main_window : public QWidget
{
    Q_OBJECT
public:
    explicit librarian_main_window(QString login, users_controller& users);

signals:

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit num_library_card;
    QLineEdit home_address;

    QLineEdit login;
    QLineEdit password;

};
