QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin_main_window/admin_main_window.cpp \
    books_controller/books_controller.cpp \
    librarian_main_window/librarian_main_window.cpp \
    main.cpp \
    reader_main_window/reader_main_window.cpp \
    reg_book/reg_book.cpp \
    reg_reader/reg_reader.cpp \
    registration/registration.cpp \
    sfu_library_solution.cpp \
    users_controller/users_controller.cpp

HEADERS += \
    admin_main_window/admin_main_window.h \
    books_controller/books_controller.h \
    librarian_main_window.h \
    librarian_main_window/librarian_main_window.h \
    reader_main_window/reader_main_window.h \
    reg_book/reg_book.h \
    reg_reader/reg_reader.h \
    registration/registration.h \
    sfu_library_solution.h \
    users_controller/users_controller.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
