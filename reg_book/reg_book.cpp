#include "reg_book.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMessageBox>

reg_book::reg_book(books_controller& books_cnr) : QDialog(nullptr), books_cnr(books_cnr) {
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Название"), 1, 1);
    QRegExp rx0("[0-9a-zA-Z-/., ]{0,}");
    book_name.setValidator(new QRegExpValidator(rx0, this));
    grid->addWidget(&book_name, 2, 1);

    QRegExp rx1("[a-zA-Z]{0,}");

    grid->addWidget(new QLabel("Фамилия автора"), 1, 2);
    auth_surname.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&auth_surname, 2, 2);

    grid->addWidget(new QLabel("Имя автора"), 1, 3);
    auth_name.setValidator(new QRegExpValidator(rx0, this));
    grid->addWidget(&auth_name, 2, 3);


    grid->addWidget(new QLabel("Отчество автора"), 1, 4);
    auth_middle_name.setValidator(new QRegExpValidator(rx1, this));
    grid->addWidget(&auth_middle_name, 2, 4);

    QRegExp rx2("\\d{13}");
    grid->addWidget(new QLabel("Число страниц"), 3, 1);
    num_pages.setValidator(new QRegExpValidator(rx2, this));
    grid->addWidget(&num_pages, 4, 1);

    grid->addWidget(new QLabel("Цена"), 3, 2);
    price.setValidator(new QRegExpValidator(rx2, this));
    grid->addWidget(&price, 4, 2);

    auto pbt = new QPushButton("Добавить книгу");
    grid->addWidget(pbt, 5, 1, 1, 4);

    connect(pbt, SIGNAL(clicked()), this, SLOT(add_book_clicked()));

    this->setLayout(grid);
}

void reg_book::add_book_clicked () {
    book_info book;
    book.book_name = book_name.text();
    book.auth.name = auth_name.text();
    book.auth.surname = auth_surname.text();
    book.auth.middle_name = auth_middle_name.text();
    book.num_pages = num_pages.text();
    book.price = price.text();

    if(!books_cnr.check_books(book)) {

        if( book_name.text().isEmpty() || auth_name.text().isEmpty()
                || auth_surname.text().isEmpty() || auth_middle_name.text().isEmpty()
                || num_pages.text().isEmpty() || price.text().isEmpty() ) {
            auto aboutDel = new QMessageBox();
            aboutDel->setText("Пустые поля недопустимы!");
            aboutDel->exec();
            return;
        }

        books_cnr.add_item(book);

        this->close();
    } else {
        auto aboutDel = new QMessageBox();
        aboutDel->setText("Такая книга\nуже зарегестрирована!");
        aboutDel->exec();
    }
}
