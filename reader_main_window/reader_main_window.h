#ifndef READER_MAIN_WINDOW_H
#define READER_MAIN_WINDOW_H

#include <QWidget>

class reader_main_window : public QWidget
{
    Q_OBJECT
public:
    explicit reader_main_window(QString user);

private:
    QString user;

};

#endif // READER_MAIN_WINDOW_H
