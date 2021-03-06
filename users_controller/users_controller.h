#pragma once

#include <QMap>
#include <QFile>
#include <QObject>

struct user_info {
    QString name;
    QString surname;
    QString middle_name;
    QString num_library_card;
    QString home_address;

    QString login;
    QString password;

    bool operator==(const user_info& a) const {
        if (this->login == a.login) {
            return true;
        } else {
            return false;
        }
    }

    bool operator<(const user_info& u) const {
        return u.login < this->login;
    }
};

class users_controller : public QObject {
    Q_OBJECT

public:
    /*!
     * \brief Класс предоставляет интерфейс для работы с данными пользователя.
     */
    explicit users_controller(QObject *parent = nullptr);

public:
    /*!
     * \brief Этот метод добавляет администратора в базу.
     * \param[in] admin - ссылка на структуру с информацией о пользователе.
     * \return true - в случае успешного добавления пользователя, false - при провале.
     */
    bool add_admin(const user_info& admin);
    /*!
     * \brief Этот метод добавляет библиотекаря в базу.
     * \param[in] librarian - ссылка на структуру с информацией о пользователе.
     * \return true - в случае успешного добавления пользователя, false - при провале.
     */
    bool add_librarian(const user_info& librarian);
    /*!
     * \brief Этот метод добавляет читателя в базу.
     * \param[in] reader - ссылка на структуру с информацией о пользователе.
     * \return true - в случае успешного добавления пользователя, false - при провале.
     */
    bool add_reader(const user_info& reader);

    /*!
     * \brief Этот метод находит администратора по его логину.
     * \param[in] login - логин.
     * \return Возвращает структуру пользователя, данные с которым совпали. Если такого нет - пустую структуру.
     */
    const user_info& get_admin (const QString login);
    /*!
     * \brief Этот метод находит библиотекаря по его логину.
     * \param[in] login - логин.
     * \return Возвращает структуру пользователя, данные с которым совпали. Если такого нет - пустую структуру.
     */
    const user_info& get_librarian (const QString login);
    /*!
     * \brief Этот метод находит читателя по его логину.
     * \param[in] login - логин.
     * \return Возвращает структуру пользователя, данные с которым совпали. Если такого нет - пустую структуру.
     */
    const user_info& get_reader (const QString login);

    /*!
     * \brief Этот метод удаляет библиотекаря по структуре librarian.
     * \param[in] librarian - ссылка на структуру с информацией о пользователе.
     * \return true - в случае успешного удаления пользователя, иначе - false.
     */
    bool remove_librarian(const user_info& librarian);
    /*!
     * \brief Этот метод удаляет библиотекаря по его логину.
     * \param[in] login - логин.
     * \return true - в случае успешного удаления пользователя, иначе - false.
     */
    bool remove_librarian(QString login);
    /*!
     * \brief Этот метод удаляет читателя по структуре user.
     * \param[in] user - ссылка на структуру с информацией о пользователе.
     * \return true - в случае успешного добавления пользователя, иначе - false.
     */
    bool remove_reader(const user_info& user);
    /*!
     * \brief Этот метод удаляет читателя по его логину.
     * \param[in] login - логин.
     * \return true - в случае успешного добавления пользователя, иначе - false.
     */
    bool remove_reader(QString login);

    /*!
     * \brief Этот метод находит количество библиотекарей в базе.
     * \return Возвращает количество библиотекарей.
     */
    int get_num_librarians ();
    /*!
     * \brief Этот метод находит количество читателей в базе.
     * \return Возвращает количество читателей.
     */
    int get_num_readers ();

    /*!
     * \brief Этот метод возвращает список библиотекарей.
     * \return возвращает список библиотекарей.
     */
    QStringList get_list_librarians ();
    /*!
     * \brief Этот метод возвращает список читателей.
     * \return возвращает список читателей.
     */
    QStringList get_list_readers ();

    /*!
     * \brief Этот метод проверяет наличие пользователя в базе.
     * \param[in] login - логин пользователя.
     * \return true - в случае наличия пользователя, false - при его отсутствии.
     */
    bool check_users_login(QString login);

    /*!
     * \brief Этот метод проверяет наличие администратора в базе
     * \param[in] login - логин администратора.
     * \return true - в случае наличия администратора, false - при его отсутствии.
     */
    bool check_admin_login(QString login);
    /*!
     * \brief Этот метод проверяет наличие библиотекаря в базе
     * \param[in] login - логин библиотекаря.
     * \return true - в случае наличия библиотекаря, false - при его отсутствии.
     */
    bool check_librarian_login(QString login);
    /*!
     * \brief Этот метод проверяет наличие читателя в базе
     * \param[in] login - логин читателя.
     * \return true - в случае наличия читателя, false - при его отсутствии.
     */
    bool check_reader_login(QString login);

private:
    QStringList get_list_users (QMap<user_info, QString> users);

private:
    QMap<user_info, QString> admins;
    QMap<user_info, QString> librarians;
    QMap<user_info, QString> readers;

private:
    bool add_user_to_map (const user_info& book, const QString file_name, QMap<user_info, QString>& users);
    bool add_user_to_file (const user_info& book, const QString file_name);

private:
    const user_info& get_user (const QString& login, QMap<user_info, QString>& users);

private:
    user_info filling_fields (QFile& file);

private:
    void extract_data_from_files (QString& dir_name, QMap<user_info, QString>& users);
    QString remove_endl (const QByteArray& s);

private:
    bool user_is_present (const QString &login);


private:
    // dir_name = "./admins"
    // dir_name = "./librarians"
    // dir_name = "./readers"
    uint64_t get_number (const QString& dir_name);
    void create_number (const QString& dir_name);
    void inc_number (const QString& dir_name);

};
