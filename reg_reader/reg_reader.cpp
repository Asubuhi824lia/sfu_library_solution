#include "reg_reader.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>

reg_reader::reg_reader(users_controller& users_cnr) : QDialog(nullptr), users_cnr(users_cnr) {
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Логин"), 8, 1);
    QRegExp rx0("[0-9a-zA-Z-/.,]{0,}");
    login.setValidator(new QRegExpValidator(rx0, this));
    grid->addWidget(&login, 9, 1);

    grid->addWidget(new QLabel("Пароль"), 8, 2);
    password.setValidator(new QRegExpValidator(rx0, this));
    grid->addWidget(&password, 9, 2);

    grid->addWidget(new QLabel("Фамилия"), 8, 3);
    QRegExp rx1("[a-zA-Z]{0,}");
    surname.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&surname, 9, 3);

    grid->addWidget(new QLabel("Имя"), 8, 4);
     name.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&name, 9, 4);

    grid->addWidget(new QLabel("Отчество"), 8, 5);
    middle_name.setValidator(new QRegExpValidator(rx1, this));

    grid->addWidget(&middle_name, 9, 5);

    QRegExp rx2("[0-9a-zA-Z-/., ]{0,}");
    home_address.setValidator(new QRegExpValidator(rx2, this));
    grid->addWidget(new QLabel("Домашний адрес"), 10, 1);
    grid->addWidget(&home_address, 11, 1);

    grid->addWidget(new QLabel("Читательский билет"), 10, 2);
    QRegExp rx3("\\d{13}");
    num_library_card.setValidator(new QRegExpValidator(rx3, this));
    grid->addWidget(&num_library_card, 11, 2);

    auto pbt = new QPushButton("Добавить читателя");
    grid->addWidget(pbt, 13, 1, 1, 7);

    this->setLayout(grid);

    connect(pbt, SIGNAL(clicked()), this, SLOT(add_reader_clicked()));
}

void reg_reader::add_reader_clicked () {
    if(!users_cnr.check_users_login(login.text())) {
        if(name.text().isEmpty() || surname.text().isEmpty()
               || middle_name.text().isEmpty() || home_address.text().isEmpty()
               || login.text().isEmpty() || password.text().isEmpty()
               || num_library_card.text().isEmpty()) {
            auto aboutDel = new QMessageBox();
            aboutDel->setText("Пустые поля недопустимы!");
            aboutDel->exec();
            return;
        }

        if (users_cnr.check_users_login(login.text())) {
            auto aboutDel = new QMessageBox();
            aboutDel->setText("Пользователь с таким логином\nуже зарегестрирован");
            aboutDel->exec();
            return;
        }

        user_info reader;
        reader.name = name.text();
        reader.surname = surname.text();
        reader.middle_name = middle_name.text();
        reader.home_address = home_address.text();
        reader.login = login.text();
        reader.password = password.text();
        reader.num_library_card = num_library_card.text();
        users_cnr.add_reader(reader);
        this->close();

    } else {
        auto aboutDel = new QMessageBox();
        aboutDel->setText("Пользователь с таким логином\nуже зарегестрирован");
        aboutDel->exec();
    }
}
