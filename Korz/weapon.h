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
    int get_id() const;
    QString get_name() const;
    int get_damage() const;
    double get_fire_rate() const;
    void set_name(QString name);
    void set_damage(int dam);
    void set_fire_rate(int fr);
    bool can_fire();
    void fire();
    ~Weapon();
private slots:
    void set_ready();
private:
    int id;
    QString name;
    int damage;
    bool ready_to_fire = true;
    double fire_rate;
    //Overloading = operator to check if two items are the same
    bool operator = (Weapon *b) {
        bool result;
        if(this->get_id() == b->get_id())
            result = true;
        else
            result = false;

        return result;
    }
    bool compare_weapons(Weapon *b);
};

#endif // WEAPON_H
