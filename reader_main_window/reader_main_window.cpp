#include "reader_main_window.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>

reader_main_window::reader_main_window(QString user) : QWidget(nullptr)
{
    QGridLayout* grid = new QGridLayout();

    grid->addWidget(new QLabel("Фонд книг"), 1, 1);
    auto tw1 = new QTableWidget();
    tw1->setColumnCount(6);
    tw1->setHorizontalHeaderLabels( {"Книга", "Автор", "Страниц", "Цена", "Читательский билет", "Дата выдачи"} );
    tw1->setColumnWidth(4, 120);
    grid->addWidget(tw1, 2, 1, 5, 2);

    grid->addWidget(new QLabel("Взятые книги"), 1, 3);
    auto tw2 = new QTableWidget();
    tw2->setColumnCount(3);
    tw2->setHorizontalHeaderLabels( {"Книга", "Автор", "Дата выдачи"} );
    grid->addWidget(tw2, 2, 3, 5, 2);

    auto bt1 = new QPushButton("Поиск книги");
    grid->addWidget(bt1, 7, 1);
    auto le1 = new QLineEdit();
    grid->addWidget(le1, 7, 2);

    auto bt2 = new QPushButton("Поиск");
    grid->addWidget(bt2, 7, 3);
    auto le2 = new QLineEdit();
    grid->addWidget(le2, 7, 4);

    setLayout(grid);
}
