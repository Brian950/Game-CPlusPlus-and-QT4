#ifndef BULLET_H
#define BULLET_H
#include "mainmenu.h"
#include "enemy.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
    Bullet(Character *parent);
    Bullet(Enemy *parent, Character *play);
    int get_damage();
    ~Bullet();
private:
    int type; ///0 = player  1 = enemy
    int damage;
    int speed;
    int direction; //0 = left 1 = right
    Character *player; //used if an enemy fires a bullet
    QPixmap pixmap;
    QTimer movement;
private slots:
    void move();

};

#endif // BULLET_H
