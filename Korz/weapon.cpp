#include "weapon.h"

Weapon::Weapon()
{
    id = 1;
    name = "Weapon";
}

int Weapon::get_id()
{
    return id;
}

QString Weapon::get_name()
{
    return name;
}

int Weapon::get_damage()
{
    return damage;
}

int Weapon::get_fire_rate()
{
    return fire_rate;
}
