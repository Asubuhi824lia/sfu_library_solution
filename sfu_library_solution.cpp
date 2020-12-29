#include "admin_main_window/admin_main_window.h"
#include "librarian_main_window/librarian_main_window.h"
#include "reader_main_window/reader_main_window.h"

#include "sfu_library_solution.h"

sfu_library_solution::sfu_library_solution(QObject *parent) : QObject(parent) {
    this->reg = new registration();
    reg->setWindowTitle("Вход в аккаунт");
    this->reg->show();

    books_controller fond;
    users_controller users;

    connect(reg, SIGNAL(enter_to_main_form(QString,QString)), this, SLOT(user_connect(QString,QString)));

}

sfu_library_solution::~sfu_library_solution() {}

void sfu_library_solution::user_connect(QString login, QString password) {
    if(login.isEmpty() || password.isEmpty()) {
        return;
    }

    auto s = users.get_admin(login);

    if (users.check_admin_login(login) || s.password == password) {
        reg->close();

        auto main_window = new admin_main_window(login, users);
        main_window->setWindowTitle("Администратор");
        main_window->show();
        return;
    }

    s = users.get_librarian(login);

    if (users.check_librarian_login(login) || s.password == password) {
        reg->close();

        auto main_window = new librarian_main_window(login, users, books);
        main_window->setWindowTitle("Библиотекарь");
        main_window->show();
        return;
    }

    s = users.get_reader(login);

    if (users.check_reader_login(login) || s.password == password) {
        reg->close();

        auto main_window = new reader_main_window(login);
        main_window->setWindowTitle("Читатель");
        main_window->show();
        return;
    }

}
