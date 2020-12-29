#include "librarian_main_window.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>


#include "reg_reader/reg_reader.h"

librarian_main_window::librarian_main_window(QString libr_login,
                                             users_controller& users,
                                             books_controller& books) :
    QWidget(nullptr), libr_login(libr_login), users_cnr(users), books_cnr(books) {

    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Читатели"), 1, 1);
    readers_list = new QListWidget();
    QStringList readers = users.get_list_readers();
    readers_list->addItems(readers);
    grid->addWidget(readers_list, 2, 1, 1, 2);

    grid->addWidget(new QLabel("Фонд книг"), 1, 3);
    tw.setColumnCount(6);
    tw.setHorizontalHeaderLabels( {"Книга", "Автор", "Страниц", "Цена", "Читательский билет", "Дата выдачи"} );
    tw.setColumnWidth(4, 120);
    grid->addWidget(&tw, 2, 3, 1, 4);

    auto bt_r1 = new QPushButton("Добавить");
    grid->addWidget(bt_r1, 3, 1, 2, 1);

    auto bt_b1 = new QPushButton("Принять книгу");
    grid->addWidget(bt_b1, 3, 3);

    auto bt_b2 = new QPushButton("Выдать книгу");
    grid->addWidget(bt_b2, 3, 4);

    auto bt_b3 = new QPushButton("Добавить книгу");
    grid->addWidget(bt_b3, 3, 5);

    auto bt_b4 = new QPushButton("Списать книгу");
    grid->addWidget(bt_b4, 3, 6);

    this->setLayout(grid);

    connect(this->readers_list, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(del_reader_clicked(QListWidgetItem *)));

    connect(bt_r1, SIGNAL(clicked()),
             this, SLOT(add_reader_clicked()));

    connect(bt_b1, SIGNAL(clicked()), this, SLOT(accept_book()));
    connect(bt_b2, SIGNAL(clicked()), this, SLOT(give_out_book()));
    connect(bt_b3, SIGNAL(clicked()), this, SLOT(add_book()));
    connect(bt_b4, SIGNAL(clicked()), this, SLOT(write_off_book()));

    this->full_table_books();
}

void librarian_main_window::accept_book () {

}

void librarian_main_window::give_out_book () {

}

void librarian_main_window::add_book () {

}

void librarian_main_window::write_off_book () {

}

void librarian_main_window::full_table_books () {
    auto v = this->books_cnr.get_books_info();

    int row = 0;
    for (auto i : v) {
        tw.setCellWidget(row, 0, new QLabel(i.book_name));
        tw.setCellWidget(row, 0, new QLabel(tr("%1 %2 %3").arg(i.auth.name).arg(i.auth.surname).arg(i.auth.middle_name)));
        tw.setCellWidget(row, 0, new QLabel(i.num_pages));
        tw.setCellWidget(row, 0, new QLabel(i.price));
        row++;
    }
}

void librarian_main_window::del_reader_clicked(QListWidgetItem* i) {
    auto aboutDel = new QMessageBox();
    aboutDel->setText("Удалить читателя?");
    aboutDel->setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    aboutDel->setDefaultButton(QMessageBox::Cancel);
    int ret = aboutDel->exec();

    switch (ret) {
        case QMessageBox::Ok:
            {
                users_cnr.remove_reader(i->text());
                readers_list->clear();
                auto readers = users_cnr.get_list_readers();
                readers_list->addItems(readers);
                break;
            }
        case QMessageBox::Cancel:
            break;
    }
}

void librarian_main_window::add_reader_clicked() {
    auto add_us_form = new reg_reader(users_cnr);
    add_us_form->setWindowTitle("Новый пользователь");
    add_us_form->exec();
    delete add_us_form;
    QStringList readers = users_cnr.get_list_readers();
    readers_list->clear();
    readers_list->addItems(readers);
}

