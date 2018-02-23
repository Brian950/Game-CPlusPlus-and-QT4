#include "character.h"

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

vector<int> Character::get_inventory()
{
    return inventory_array;
}

void Character::set_inventory(vector<int> i)
{
    inventory_array = i;
}

