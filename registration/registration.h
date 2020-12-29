#pragma once

#include <QList>
#include <QWidget>
#include <QLineEdit>

class registration : public QWidget
{
    Q_OBJECT
public:
    explicit registration(QWidget *parent = nullptr);

signals:
    void enter_to_main_form (QString login, QString password);

public slots:
    void send_info();

private:
    QLineEdit login;
    QLineEdit password;

};
