#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "weapon.h"
#include "medkit.h"
class Enemy;

using namespace std;

class Character : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString name;
    int strength;
    int speed;
    int guns;
    int luck;
    int special_ability;
    int location;
    int direction; //0 = left  1 = right
    int health;
    int max_health;
    Weapon *current_weapon;
    QString inventory_string; //String of item ids separated by ':' to store inventory.
    int x_limit; //Sets limit on where on the screen the player can move to
    QList<Enemy*> *active_enemies;

public:
    Character();
    Character(QString, int, int, int, int, int, QList<Enemy*>*);
    QPixmap right_pixmap;
    QPixmap left_pixmap;
    QString get_name();
    QSet<int> pressedKeys; //Holds all currently held down keys
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void set_name(QString);
    int get_strength();
    void set_strength(int);
    int get_speed();
    void set_speed(int);
    int get_guns();
    void set_guns(int);
    int get_luck();
    void set_luck(int);
    int get_special();
    void set_special(int);
    int get_location();
    void set_location(int);
    int get_health();
    void set_health(int);
    int get_x_limit();
    void set_x_limit(int);
    int get_direction();
    QString get_inventory();
    int add_item_to_inventory(int);
    void set_inventory(QString);
    int get_inventory_size();
    void remove_item_from_inventory(int id);
    void set_current_weapon(Weapon*);
    Weapon* get_current_weapon();
    void use_medkit(Medkit*);
    void hit(int dam);
    void die();
signals:
    void update_health();
};

#endif // CHARACTER_H
