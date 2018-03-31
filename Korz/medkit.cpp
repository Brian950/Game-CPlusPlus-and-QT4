#include "medkit.h"

Medkit::Medkit()
{
    id = 2;
    name = "Medkit";
    health = 25;
}

Medkit::Medkit(int i, QString n, int hp)
{
    id = i;
    name = n;
    health = hp;
}

int Medkit::get_id()
{
    return id;
}

QString Medkit::get_name()
{
    return name;
}

int Medkit::get_health()
{
    return health;
}

Medkit::~Medkit(){}
