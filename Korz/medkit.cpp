#include "medkit.h"

Medkit::Medkit()
{
    id = 2;
    name = "Medkit";
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
