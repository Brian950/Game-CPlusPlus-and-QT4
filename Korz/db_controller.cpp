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

int DB_Controller::add_player(int id, QString name, int str, int spd, int gun, int lck, int special, int loc, int hp, QString inv)
{
    QSqlQuery check_characters;
    int number_of_chars_with_this_name = 0;
    check_characters.prepare("SELECT name FROM characters WHERE name = :name");
    check_characters.bindValue(":name", name);
    if (check_characters.exec()) {
        while (check_characters.next()) {
            number_of_chars_with_this_name++;
        }
        if(number_of_chars_with_this_name > 0){
            check_characters.finish();
            return 1;
        }
    }
    else{
        std::cout << "Failure\n";
        return 1;
    }

    QSqlQuery insert_character;
    insert_character.prepare("INSERT INTO characters (id, name, strength, speed, guns, luck, special, location, health, inventory) VALUES (:id, :name, :str, :spd, :gun, :lck, :special, :loc, :hp, :inv)");
    insert_character.bindValue(":name", name); insert_character.bindValue(":str",str);
    insert_character.bindValue(":spd",spd); insert_character.bindValue(":gun", gun);
    insert_character.bindValue(":lck",lck); insert_character.bindValue(":special",special);
    insert_character.bindValue(":loc",loc); insert_character.bindValue(":hp",hp);
    insert_character.bindValue(":inv",inv); insert_character.bindValue(":id",id);

    if(insert_character.exec())
    {
        std::cout << "Success on INSERT\n";
        return 0;
    }
    else{
        std::cout << "Failure on INSERT\n";
        return 1;
    }
}

int DB_Controller::number_of_characters(){
    QSqlQuery check_characters;
    int number_of_chars= 0;
    check_characters.prepare("SELECT name FROM characters");
    if(check_characters.exec()){
        while(check_characters.next())
            number_of_chars++;

        return number_of_chars;
    }
    else{
        std::cout << "Failure on character count SELECT\n";
    }
}

void DB_Controller::clear_character_table(){
    QSqlQuery clear_characters;
    clear_characters.prepare("DELETE FROM characters");
    clear_characters.exec();
}

QString DB_Controller::get_item_name(int id){
    QString name = "not_found";
    QSqlQuery get_name;
    get_name.prepare("SELECT name FROM items WHERE id = :id");
    get_name.bindValue(":id",id);
    if(get_name.exec()){
        while(get_name.next()){
            name = get_name.value(0).toString();
            return name;
        }
    }
    return name;
}

int DB_Controller::get_item_id(QString name){
    int id = 0;
    QSqlQuery get_id;
    get_id.prepare("SELECT id FROM items WHERE name = :name");
    get_id.bindValue(":name",name);
    if(get_id.exec()){
        while(get_id.next()){
            id = get_id.value(0).toInt();
            return id;
        }
    }
    return id;
}
