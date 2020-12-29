#include "registration.h"

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QRegExpValidator>

registration::registration(QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout();
    QRegExp rx ("[a-zA-Z]{0,}");

    grid->addWidget(new QLabel("login"), 1,1);

    login.setValidator(new QRegExpValidator(rx, this));
    grid->addWidget(&login, 1,2);

    grid->addWidget(new QLabel("password"), 2,1);

    password.setValidator(new QRegExpValidator(rx, this));
    grid->addWidget(&password, 2,2);


    QPushButton* ppb = new QPushButton(tr("Entrance"), this);
    grid->addWidget(ppb, 3, 3);

    setLayout(grid);

    connect( ppb, SIGNAL(clicked()), this, SLOT(send_info()));
}

void registration::send_info() {
    emit enter_to_main_form (login.text(), password.text());
}
