#ifndef REG_BOOK_H
#define REG_BOOK_H

#include "books_controller/books_controller.h"

#include <QWidget>
#include <QDialog>
#include <QLineEdit>

class reg_book : public QDialog
{
    Q_OBJECT
public:
    explicit reg_book(books_controller& books_cnr);

private:
    QLineEdit book_name;
    QLineEdit auth_name;
    QLineEdit auth_surname;
    QLineEdit auth_middle_name;
    QLineEdit num_pages;
    QLineEdit price;

private:
    /// Это переменная.
    books_controller& books_cnr;

private slots:
    void add_book_clicked ();

};

#endif // REG_BOOK_H
