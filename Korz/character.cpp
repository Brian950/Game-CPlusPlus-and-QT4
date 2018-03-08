#include "character.h"
#include <QDebug>

Character::Character()
{
}

Character::Character(QString n, int str, int spd, int gn, int lk, int spc)
{
    name = n;
    strength = str;
    speed = spd;
    guns = gn;
    luck = lk;
    special_ability = spc;
    location = 0;
    health = 100;
    inventory_array.reserve(5+str);
    character_pixmap = QPixmap(":/Icons/soldier.png");
    moveable = true;
    x_limit = 850;
    setFlag(QGraphicsItem::ItemIsFocusable);
    setPixmap(character_pixmap);
    setScale(0.2);
}

void Character::keyPressEvent(QKeyEvent *event)
{
    pressedKeys += (event)->key(); //When a key is pressed it gets stored in this array. When it is released it gets removed.

    if(pressedKeys.size() == 1){
        if(pressedKeys.contains(Qt::Key_D) && x() < 850 && x() < x_limit){
            setPos(x()+10+speed, y());
            qDebug() << " " << x() << " ";
        }
        else if(pressedKeys.contains(Qt::Key_A) && x() > -50){
            setPos(x()-10-speed, y());
        }
        else if(pressedKeys.contains(Qt::Key_W) && y() > -250){
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && y() < 250){
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_Space)){

        }
    }
    else if(pressedKeys.size() == 2){
        if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() > -250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_Space) && y() < 250){
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_Space) && y() > -250){
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50){
            setPos(x()-10-speed, y());
        }
        else if(pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && x() < x_limit){
            setPos(x()+10+speed, y());
        }
    }
    else if(pressedKeys.size() == 3){
        if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() > -250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && y() > -250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
        }
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys -= (event)->key();
}



QString Character::get_name()
{
    return name;
}

void Character::set_name(QString n)
{
    name = n;
}

int Character::get_strength()
{
    return strength;
}

void Character::set_strength(int s)
{
    strength = s;
}

int Character::get_speed()
{
    return speed;
}

void Character::set_speed(int s)
{
    speed = s;
}

int Character::get_guns()
{
    return guns;
}

void Character::set_guns(int g)
{
    guns = g;
}

int Character::get_luck(){
    return luck;
}

void Character::set_luck(int l)
{
    luck = l;
}

int Character::get_special()
{
    return special_ability;
}

void Character::set_special(int s)
{
    special_ability = s;
}

int Character::get_location()
{
    return location;
}

void Character::set_location(int l)
{
    location = l;
}

int Character::get_health()
{
    return health;
}

void Character::set_health(int h)
{
    health = h;
}

void Character::set_x_limit(int limit){
    x_limit = limit;
}

vector<int> Character::get_inventory()
{
    return inventory_array;
}

void Character::set_inventory(vector<int> i)
{
    inventory_array = i;
}

