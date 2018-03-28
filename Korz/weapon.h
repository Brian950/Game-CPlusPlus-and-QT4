#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"

class Weapon : public Item
{
public:
    Weapon();
    int get_id();
    QString get_name();
    int get_damage();
    int get_fire_rate();
private:
    int id;
    QString name;
    int damage;
    int fire_rate;
};

#endif // WEAPON_H
