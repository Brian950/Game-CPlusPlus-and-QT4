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
    void add_player(QString, int, int, int, int, int, int, int, QString);
private:
    QSqlDatabase kroz_db;
};

#endif // DB_CONTROLLER_H
