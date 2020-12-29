#pragma once

#include "books_controller/books_controller.h"
#include "users_controller/users_controller.h"
#include "registration/registration.h"

#include <QWidget>

class sfu_library_solution : public QObject {
    Q_OBJECT

public:
    sfu_library_solution(QObject *parent = nullptr);
    ~sfu_library_solution();

private slots:
    void user_connect(QString login, QString password);

private:
    registration* reg;

    books_controller fond;
    users_controller users;

};
