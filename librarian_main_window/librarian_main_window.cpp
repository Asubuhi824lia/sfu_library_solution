#include "librarian_main_window.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QTableWidget>

librarian_main_window::librarian_main_window(QString login, users_controller& users) : QWidget(nullptr)
{
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Читатели"), 1, 1);
    auto lw = new QListWidget();
    QStringList readers = users.get_list_readers();
    lw->addItems(readers);
    grid->addWidget(lw, 2, 1, 1, 2);

    grid->addWidget(new QLabel("Фонд книг"), 1, 3);
    auto tw = new QTableWidget();
    tw->setColumnCount(6);
    tw->setHorizontalHeaderLabels( {"Книга", "Автор", "Страниц", "Цена", "Читательский билет", "Дата выдачи"} );
    tw->setColumnWidth(4, 120);    
    grid->addWidget(tw, 2, 3, 1, 4);

    auto bt_r1 = new QPushButton("Добавить");
    grid->addWidget(bt_r1, 3, 1);

    auto bt_r2 = new QPushButton("Удалить");
    grid->addWidget(bt_r2, 3, 2);


    auto bt_b1 = new QPushButton("Принять книгу");
    grid->addWidget(bt_b1, 3, 3);

    auto bt_b2 = new QPushButton("Выдать книгу");
    grid->addWidget(bt_b2, 3, 4);

    auto bt_b3 = new QPushButton("Добавить книгу");
    grid->addWidget(bt_b3, 3, 5);

    auto bt_b4 = new QPushButton("Списать книгу");
    grid->addWidget(bt_b4, 3, 6);

//    grid->addWidget(new QLabel("Логин"), 8, 1);
//    grid->addWidget(&login, 9, 1);

//    grid->addWidget(new QLabel("Пароль"), 8, 2);
//    grid->addWidget(&password, 9, 2);

//    grid->addWidget(new QLabel("Фамилия"), 8, 3);
//    grid->addWidget(&surname, 9, 3);

//    grid->addWidget(new QLabel("Имя"), 8, 4);
//    grid->addWidget(&name, 9, 4);

//    grid->addWidget(new QLabel("Отчество"), 8, 5);
//    grid->addWidget(&middle_name, 9, 5);

//    grid->addWidget(new QLabel("Домашний адрес"), 10, 1);
//    grid->addWidget(&home_address, 11, 1);

//    grid->addWidget(new QLabel("Читательский билет"), 10, 2);
//    grid->addWidget(&num_library_card, 11, 2);

//    auto pbt = new QPushButton("Добавить читателя");
//    grid->addWidget(pbt, 13, 1, 1, 7);

    setLayout(grid);
}
