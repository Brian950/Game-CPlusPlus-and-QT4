#ifndef MEDKIT_H
#define MEDKIT_H
#include "item.h"

class Medkit : public Item
{
public:
    Medkit();
    Medkit(int, QString, int);
    int get_id();
    QString get_name();
    int get_health();
    virtual ~Medkit(); //This is necessary as Medkit is derived from item. It makes sure the top destructor is called
private:
    int id;
    QString name;
    int health;
};

#endif // MEDKIT_H
