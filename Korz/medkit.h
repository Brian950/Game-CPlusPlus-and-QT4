#ifndef MEDKIT_H
#define MEDKIT_H
#include "item.h"

class Medkit : public Item
{
public:
    Medkit();
    int get_id();
    QString get_name();
    int get_health();
private:
    int id;
    QString name;
    int health;
};

#endif // MEDKIT_H
