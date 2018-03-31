#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"
#include <QTimer>

class Weapon : public QObject, public Item
{
    Q_OBJECT
public:
    Weapon();
    Weapon(int, QString, int, double);
    int get_id();
    QString get_name();
    int get_damage();
    double get_fire_rate();
    void set_name(QString name);
    void set_damage(int dam);
    void set_fire_rate(int fr);
    bool can_fire();
    void fire();
    virtual ~Weapon(); //This is necessary as Weapon is derived from item. It makes sure the top destructor is called
private slots:
    void set_ready();
private:
    int id;
    QString name;
    int damage;
    bool ready_to_fire = true;
    double fire_rate;
};

#endif // WEAPON_H
