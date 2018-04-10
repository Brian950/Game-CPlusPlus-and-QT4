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

int Medkit::get_id() const
{
    return id;
}

QString Medkit::get_name() const
{
    return name;
}

bool Medkit::compare_medkits(Medkit *b){
    if(b = this)
        return true;
    else
        return false;
}

int Medkit::get_health() const
{
    return health;
}

Medkit::~Medkit(){}
