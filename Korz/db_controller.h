#ifndef DB_CONTROLLER_H
#define DB_CONTROLLER_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>


class DB_Controller
{
public:
    DB_Controller(const QString&);
    int add_player(int, QString, int, int, int, int, int, int, int, QString);
    void clear_character_table();
    int number_of_characters();
    QString get_item_name(int);
    int get_item_id(QString name);
private:
    QSqlDatabase kroz_db;
};

#endif // DB_CONTROLLER_H
