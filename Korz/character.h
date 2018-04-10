#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include <QString>
#include <QSoundEffect>
#include <QKeyEvent>
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
    double health;
    double max_health;
    Weapon *current_weapon;
    QString inventory_string; //String of item ids separated by ':' to store inventory.
    int x_limit; //Sets limit on where on the screen the player can move to
    QList<Enemy*> *active_enemies;
    QSoundEffect *gun_shot;

public:
    Character();
    Character(QString, int, int, int, int, int, QList<Enemy*>*);
    ~Character();
    QPixmap right_pixmap;
    QPixmap left_pixmap;
    QString get_name() const;
    QSet<int> pressedKeys; //Holds all currently held down keys
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void set_name(QString);
    int get_strength() const;
    void set_strength(int);
    int get_speed() const;
    void set_speed(int);
    int get_guns() const;
    void set_guns(int);
    int get_luck() const;
    void set_luck(int);
    int get_special() const;
    void set_special(int);
    int get_location() const;
    void set_location(int);
    int get_health() const;
    void set_health(int);
    int get_max_health() const;
    int get_x_limit() const;
    void set_x_limit(int);
    int get_direction() const;
    QString get_inventory() const;
    int add_item_to_inventory(int);
    void set_inventory(QString);
    int get_inventory_size() const;
    void remove_item_from_inventory(int id);
    void set_current_weapon(Weapon*);
    Weapon* get_current_weapon() const;
    void use_medkit(Medkit*);

    template <typename T>
    void hit(T dam, int enemy_type)
    {
        if(enemy_type == 3){
            QSoundEffect *explosion = new QSoundEffect(this);
            explosion->setSource(QUrl::fromLocalFile(":/Sounds/explosion.wav"));
            explosion->play();
        }
        if(health - dam < 1){
            health = 0;
            emit update_health();
            die();
        }
        else{
            health = health-dam;
            emit update_health();
        }
    }

    void die();
    void clean_up();
signals:
    void update_health();
};

#endif // CHARACTER_H
