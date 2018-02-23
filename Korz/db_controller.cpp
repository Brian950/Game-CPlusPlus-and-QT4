#include "db_controller.h"
#include <iostream>

DB_Controller::DB_Controller(const QString& path)
{
    kroz_db = QSqlDatabase::addDatabase("QSQLITE");
    kroz_db.setDatabaseName(path);

    if (!kroz_db.open())
    {
      std::cout << "Connection Failed\n";
    }
    else
    {
      std::cout << "Successfully Connected\n";
    }
}

void DB_Controller::add_player(QString name, int str, int spd, int gun, int lck, int special)
{
    QSqlQuery insert_character;
    insert_character.prepare("INSERT INTO character (name, str, spd, gun, lck, special) VALUES (:name, :str, :spd, :gun, :lck, :special)");
    insert_character.bindValue(":name", name); insert_character.bindValue(":str",str);
    insert_character.bindValue(":spd",spd); insert_character.bindValue(":gun", gun);
    insert_character.bindValue(":lck",lck); insert_character.bindValue(":special",special);
    if(insert_character.exec())
    {
        std::cout << "Success\n";
    }
    else
        std::cout << "Failure\n";

    QSqlQuery test;
    QString player_name;
    test.prepare("SELECT name FROM character WHERE name = (:name)");
    test.bindValue(":name", player_name);

    if (test.exec())
    {
       if (test.next())
       {
          std::cout << "At least two found.\n";
       }
    }
}
