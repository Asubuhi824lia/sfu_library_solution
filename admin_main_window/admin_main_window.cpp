#include "users_controller/users_controller.h"
#include "admin_main_window.h"

#include <QLabel>
#include <QRegExp>
#include <QValidator>
#include <QGridLayout>
#include <QMessageBox>
#include <QRegExpValidator>

admin_main_window::admin_main_window(QString user, users_controller& users_cnr) : QWidget(nullptr), user(user), users_cnr(users_cnr) {
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Библиотекари"), 1, 1);

    QStringList librarians = users_cnr.get_list_librarians();
    this->librarians_list = new QListWidget();
    librarians_list->addItems(librarians);
    grid->addWidget(librarians_list, 2, 1, 1, 1);

    grid->addWidget(new QLabel("Читатели"), 1, 3);

    QStringList readers = users_cnr.get_list_readers();
    this->readers_list = new QListWidget();
    readers_list->addItems(readers);
    grid->addWidget(readers_list, 2, 3, 1, 1);

    grid->addWidget(new QLabel("Фамилия"), 8, 1);
    QRegExp rx1("[a-zA-Z]{0,}");
    surname.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&surname, 9, 1);

    grid->addWidget(new QLabel("Имя"), 8, 2);
    name.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&name, 9, 2);

    grid->addWidget(new QLabel("Отчество"), 8, 3);
    middle_name.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&middle_name, 9, 3);

    QRegExp rx2("[0-9a-zA-Z-/., ]{0,}");
    home_address.setValidator(new QRegExpValidator(rx2, this));
    grid->addWidget(new QLabel("Домашний адрес"), 10, 1);
    grid->addWidget(&home_address, 11, 1);

    grid->addWidget(new QLabel("Логин"), 12, 1);
    QRegExp rx3("[0-9a-zA-Z-/.,]{0,}");
    login.setValidator(new QRegExpValidator(rx3, this));
    grid->addWidget(&login, 13, 1);

    grid->addWidget(new QLabel("Пароль"), 12, 2);
    password.setValidator(new QRegExpValidator(rx3, this));
    grid->addWidget(&password, 13, 2);

    auto pbt = new QPushButton("Добавить библиотекаря");
    grid->addWidget(pbt, 16, 1, 1, 3);

    this->setLayout(grid);

    connect(this->librarians_list, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(del_librarian_clicked(QListWidgetItem *)));

    connect(pbt, SIGNAL(clicked()),
             this, SLOT(add_librarian_clicked()));
}

void admin_main_window::del_librarian_clicked(QListWidgetItem* i) {
    auto aboutDel = new QMessageBox();
    aboutDel->setText("Удалить библиотекаря?");
    aboutDel->setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    aboutDel->setDefaultButton(QMessageBox::Cancel);
    int ret = aboutDel->exec();

    switch (ret) {
        case QMessageBox::Ok:
            {
                users_cnr.remove_librarian (i->text());
                librarians_list->clear();
                auto librarians = users_cnr.get_list_librarians();
                librarians_list->addItems(librarians);
                break;
            }
        case QMessageBox::Cancel:
            break;
    }
}

void admin_main_window::add_librarian_clicked() {
    if(!users_cnr.check_users_login(login.text())) {
        if(name.text().isEmpty() || surname.text().isEmpty()
               || middle_name.text().isEmpty() || home_address.text().isEmpty()
               || login.text().isEmpty() || password.text().isEmpty()) {
            auto aboutDel = new QMessageBox();
            aboutDel->setText("Пустые поля недопустимы!");
            aboutDel->exec();
            return;
        }

        user_info libr;
        libr.name = name.text();
        libr.surname = surname.text();
        libr.middle_name = middle_name.text();
        libr.home_address = home_address.text();
        libr.login = login.text();
        libr.password = password.text();
        users_cnr.add_librarian(libr);

        librarians_list->clear();
        auto librarians = users_cnr.get_list_librarians();
        librarians_list->addItems(librarians);

    } else {
        auto aboutDel = new QMessageBox();
        aboutDel->setText("Пользователь с таким логином\nуже зарегестрирован");
        aboutDel->exec();
    }
}


