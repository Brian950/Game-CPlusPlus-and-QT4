#ifndef ENEMY_H
#define ENEMY_H
#include <QPixmap>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
class Character;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy();
    Enemy(int t, Character *play, QPoint position);
    void hit(int dam);
    int get_damage() const;
    int get_direction() const;
    int get_fire_rate() const;
    int get_type() const;
    ~Enemy();
private:
    int type;//Types: 1=normal{average attr} 2=fast{low health, high speed, avg dam, high aggro} 3={high health, slow, high dam,}
    int health;
    int damage;
    int direction;//0 = left  1 = right
    int fire_rate;
    int speed;
    int aggro;//How close the enemy wants to get to the player
    QPixmap pixmap_left;
    QPixmap pixmap_right;
    QPixmap pixmap_dead_left;
    QPixmap pixmap_dead_right;
    QTimer *movement;
    QTimer *shooting;
    QSoundEffect *gun_shot;
    Character *player;
    void die();
    void destroy();
private slots:
    void move();
    void shoot();
signals:
    void dead();

};

#endif // ENEMY_H
