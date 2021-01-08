#include "sfu_library_solution.h"
#include "books_controller/books_controller.h"
#include "users_controller/users_controller.h"
#include "registration/registration.h"

#include <iostream>

#include <QApplication>

void Tests_books() {
    book_info book1;
    book1.book_name = "Leaving Time";
    book1.num_pages = "320";
    book1.price = "240";
    book1.auth.name = "Jodi";
    book1.auth.surname = "Picoult";
    book1.auth.middle_name = "Lynn";

    book_info book2;
    book2.book_name = "1st to Die";
    book2.num_pages = "190";
    book2.price = "240";
    book2.auth.name = "James";
    book2.auth.surname = "Patterson";
    book2.auth.middle_name = "Brendan";

    book_info book3;
    book3.book_name = "Mr. Mercedes";
    book3.num_pages = "606";
    book3.price = "600";
    book3.auth.name = "Stephen";
    book3.auth.surname = "King";
    book3.auth.middle_name = "Edwin";

    book_info book4;
    book4.book_name = "Three men in a boat (to say nothing of the dog)";
    book4.num_pages = "208";
    book4.price = "589";
    book4.auth.name = "Jerome";
    book4.auth.surname = "K.";
    book4.auth.middle_name = "Jerome";

    book_info book5;
    book5.book_name = "Yu-Yu. Watchdog and Zhulka. Starlings. Peregrine Falcon. Elephant ride. Zaviraika";
    book5.num_pages = "64";
    book5.price = "149";
    book5.auth.name = "Alexander";
    book5.auth.surname = "Kuprin";
    book5.auth.middle_name = "Ivanovich";

    books_controller fond;
    int num = fond.get_num_items();
    fond.add_item(book1);
    fond.add_item(book2);
    fond.add_item(book3);
    fond.add_item(book4);
    fond.add_item(book5);
    num = fond.get_num_items();


    author_info auth;
    auth.name = "Stephen";
    auth.surname = "King";
    auth.middle_name = "Edwin";
    fond.remove_item(auth, "Mr. Mercedes");
    num = fond.get_num_items();
}

void Tests_users() {
    user_info librarian1;
    librarian1.login = "IvanovIvan";
    librarian1.password = "1111";
    librarian1.name = "Ivan";
    librarian1.surname = "Ivanov";
    librarian1.middle_name = "Ivanovich";
    librarian1.num_library_card = "0123456789012";
    librarian1.home_address = "st. Krasnaya, 4";

    user_info librarian2;
    librarian2.login = "Ilya Ilyov";
    librarian2.password = "1234";
    librarian2.name = "Ilya";
    librarian2.surname = "Ilyov";
    librarian2.middle_name = "Ilyich";
    librarian2.num_library_card = "8888888888887";
    librarian2.home_address = "avenue Krasnoarmeyskiy, 8";

    user_info reader1;
    reader1.login = "login1";
    reader1.password = "passw";
    reader1.name = "Petya";
    reader1.surname = "Petrov-Smirnov";
    reader1.middle_name = "Petrovich";
    reader1.num_library_card = "8800222353500";
    reader1.home_address = "st. Krasnaya, 116";

    user_info reader2;
    reader2.login = "login2";
    reader2.password = "parol";
    reader2.name = "Sasha";
    reader2.surname = "Aleksandrova";
    reader2.middle_name = "Aleksandrovna";
    reader2.num_library_card = "222022";
    reader2.home_address = "ул. Green, 1";

    user_info reader3;
    reader3.login = "login3";
    reader3.password = "PaSsW";
    reader3.name = "Kolya";
    reader3.surname = "Nikolayev";
    reader3.middle_name = "Nikolayevich";
    reader3.num_library_card = "00110011441388887225";
    reader3.home_address = "st. Naberejnaya, 19";

    users_controller users;
    int num_readers = users.get_num_readers();
    int num_librarians = users.get_num_librarians();
    users.add_librarian(librarian1);
    users.add_librarian(librarian2);
    users.add_reader(reader1);
    users.add_reader(reader2);
    users.add_reader(reader3);
    num_readers = users.get_num_readers();
    num_librarians = users.get_num_librarians();


    users.remove_reader(reader2);
    user_info r;
    r.login = reader3.login;
    users.remove_librarian(librarian1);
    num_readers = users.get_num_readers();
    num_librarians = users.get_num_librarians();

}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    sfu_library_solution w;

//    Tests_users();

    return a.exec();
}
