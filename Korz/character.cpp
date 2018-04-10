#include "character.h"
#include "bullet.h"
#include <QDebug>


Character::Character()
{
}

Character::Character(QString n, int str, int spd, int gn, int lk, int spc, QList<Enemy*> *enemies)
{
    name = n;
    strength = str;
    speed = spd;
    guns = gn;
    luck = lk;
    special_ability = spc;
    location = 0;
    max_health = 100+(str*3);
    health = max_health;
    direction = 1;
    inventory_string = "1:4";
    right_pixmap = QPixmap(":/Icons/soldier.png");
    left_pixmap = QPixmap(":/Icons/soldier-left.png");
    active_enemies = enemies;
    x_limit = 850;
    gun_shot = new QSoundEffect(this);
    gun_shot->setSource(QUrl::fromLocalFile(":/Sounds/gun_shot.wav"));
    set_current_weapon(new Weapon(0, "default", 10, 3));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setPixmap(right_pixmap);
    setScale(0.2);
}

Character::~Character()
{
}

void Character::keyPressEvent(QKeyEvent *event)
{
    pressedKeys += (event)->key(); //When a key is pressed it gets stored in this array. When it is released it gets removed.

    if(pressedKeys.contains(Qt::Key_Space)){
        if(current_weapon->can_fire()){
            if(gun_shot->isPlaying())
                gun_shot->stop();
            gun_shot->play();
            current_weapon->fire();
            Bullet *bullet = new Bullet(this, active_enemies);
            scene()->addItem(bullet);
        }
    }
    if(pressedKeys.size() == 1){
        if(pressedKeys.contains(Qt::Key_D) && x() < 850 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_A) && x() > -50){
            setPos(x()-10-speed, y());
            setPixmap(left_pixmap);
            direction = 0;
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
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
            setPixmap(left_pixmap);
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(left_pixmap);
            direction = 0;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_Space) && y() < 250){
            setPos(x(), y()+10+speed);
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_Space) && y() > -250){
            setPos(x(), y()-10-speed);
        }
        else if(pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50){
            setPos(x()-10-speed, y());
            setPixmap(left_pixmap);
            direction = 0;
        }
        else if(pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPixmap(right_pixmap);
            direction = 1;
        }
    }
    else if(pressedKeys.size() == 3){
        if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() > -250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()-10-speed);
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
            setPixmap(left_pixmap);
            direction = 0;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(left_pixmap);
            direction = 0;
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && y() > -250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()-10-speed);
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50 && y() > -250){
            setPos(x()-10-speed, y());
            setPos(x(), y()-10-speed);
            setPixmap(left_pixmap);
            direction = 0;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_D) && pressedKeys.contains(Qt::Key_Space) && x() < 850 && y() < 250 && x() < x_limit){
            setPos(x()+10+speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(right_pixmap);
            direction = 1;
        }
        else if(pressedKeys.contains(Qt::Key_S) && pressedKeys.contains(Qt::Key_A) && pressedKeys.contains(Qt::Key_Space) && x() > -50 && y() < 250){
            setPos(x()-10-speed, y());
            setPos(x(), y()+10+speed);
            setPixmap(left_pixmap);
            direction = 0;
        }
    }
}

void Character::keyReleaseEvent(QKeyEvent *event)
{
    pressedKeys -= (event)->key();
}

QString Character::get_name() const
{
    return name;
}

void Character::set_name(QString n)
{
    name = n;
}

int Character::get_strength() const
{
    return strength;
}

void Character::set_strength(int s)
{
    strength = s;
}

int Character::get_speed() const
{
    return speed;
}

void Character::set_speed(int s)
{
    speed = s;
}

int Character::get_guns() const
{
    return guns;
}

void Character::set_guns(int g)
{
    guns = g;
}

int Character::get_luck() const
{
    return luck;
}

void Character::set_luck(int l)
{
    luck = l;
}

int Character::get_special() const
{
    return special_ability;
}

void Character::set_special(int s)
{
    special_ability = s;
}

int Character::get_location() const
{
    return location;
}

void Character::set_location(int l)
{
    location = l;
}

int Character::get_health() const
{
    return health;
}

void Character::set_health(int h)
{
    health = h;
}

int Character::get_max_health() const
{
    return max_health;
}

int Character::get_x_limit() const
{
    return x_limit;
}

void Character::set_x_limit(int limit)
{
    x_limit = limit;
}

int Character::get_direction()const
{
    return direction;
}

QString Character::get_inventory() const
{
    return inventory_string;
}

void Character::set_inventory(QString i)
{
    inventory_string = i;
}

int Character::get_inventory_size() const
{
    QStringList item_list = inventory_string.split(":");
    if(item_list.length() > 0)
        return item_list.length();
    else if(inventory_string.length() == 1 && inventory_string == "")
        return 0;
    else if(inventory_string.length() == 1)
        return 1;
    else
        return 0;
}

void Character::remove_item_from_inventory(int id)
{
    QStringList item_list = inventory_string.split(":");

    if(item_list.length() > 0){
        bool removed = false;
        for(int x = 0; x < item_list.length(); x++){
            if(!removed){
                if(item_list.at(x).toInt() == id){
                    item_list.removeAt(x);
                    removed = true;
                }
            }
        }
    }

    if(item_list.length() == 0){
        inventory_string = "";
    }
    else{
        for(int x = 0; x < item_list.length(); x++){
            if(x == 0){
                inventory_string = item_list.at(x);
            }
            else{
                inventory_string.append(":"+item_list.at(x));
            }
        }
    }
}

int Character::add_item_to_inventory(int id){
    QStringList item_list = inventory_string.split(":");
    if(inventory_string.length() == 0){
        inventory_string = QString::number(id);
        return 0;
    }
    else if(inventory_string.length() == 1){
        inventory_string.append(":"+QString::number(id));
        return 0;
    }
    else if(item_list.length() < 10){
        inventory_string.append(":"+QString::number(id));
        return 0;
    }
    else{
        return 1;
    }
}

void Character::set_current_weapon(Weapon *w){
    delete current_weapon;
    current_weapon = w;
}

Weapon* Character::get_current_weapon() const
{
    return current_weapon;
}

void Character::use_medkit(Medkit *m){
    int hp = m->get_health();
    if(get_health() + hp > max_health){
        set_health(max_health);
    }
    else{
        set_health(get_health()+hp);
    }
}

void Character::die()
{

}

void Character::clean_up(){
    delete current_weapon;
}

