#ifndef REG_READER_H
#define REG_READER_H

#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>

#include "users_controller/users_controller.h"

class reg_reader : public QDialog {
    Q_OBJECT

public:
    explicit reg_reader(users_controller& users_cnr);

private:
    QLineEdit name;
    QLineEdit surname;
    QLineEdit middle_name;
    QLineEdit num_library_card;
    QLineEdit home_address;

    QLineEdit login;
    QLineEdit password;

private slots:
    void add_reader_clicked ();

private:
    users_controller& users_cnr;

};

#endif // REG_READER_H
