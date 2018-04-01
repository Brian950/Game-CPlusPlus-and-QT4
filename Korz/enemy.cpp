#include "enemy.h"
#include "bullet.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int t, Character *play, QPoint position)
{
    type = t;

    if(type == 1){
        health = 75;
        speed = 5;
        aggro = 10;
        fire_rate = 10;
        damage = 15;
    }
    else if(type == 2){
        health = 50;
        speed = 10;
        aggro = 20;
        fire_rate = 10;
        damage = 15;
    }
    else if(type == 3){
        health = 75;
        speed = 1;
        aggro = 5;
        fire_rate = 5;
        damage = 25;
    }

    player = play;
    pixmap_left = QPixmap(":/Icons/enemy_left.png");
    pixmap_right = QPixmap(":/Icons/enemy.png");
    pixmap_dead_left = QPixmap(":/Icons/enemy_left_dead.png");
    pixmap_dead_right = QPixmap(":/Icons/enemy_right_dead.png");
    setScale(2);
    setPos(position);
    if(player->x() > x()){
        direction = 1;
        setPixmap(pixmap_right);
    }
    else{
        direction = 0;
        setPixmap(pixmap_left);
    }

    movement = new QTimer();
    connect(movement, SIGNAL(timeout()), this, SLOT(move()));
    movement->start(200/speed);

    shooting = new QTimer();
    connect(shooting, SIGNAL(timeout()), this, SLOT(shoot()));
    shooting->start(100*fire_rate);
}

void Enemy::hit(int dam)
{
    health = health - dam;
    if(health < 1)
        die();
}

int Enemy::get_damage()
{
    return damage;
}

int Enemy::get_fire_rate()
{
    return fire_rate;
}

int Enemy::get_direction(){
    return direction;
}

void Enemy::move()
{
    int x1, x2, y1, y2;
    x1 = player->x();
    x2 = x();
    y1 = player->y();
    y2 = y();
    int distance = sqrt((x2 - x1)*(x2 - x1) + (y2 - y2)*(y2 - y1));

    if(player->x() > x()){
        direction = 1;
        setPixmap(pixmap_right);
        if(distance > 300){
            if(x1 > x2)
                setPos(x()+1, y());
            if(x1 < x2)
                setPos(x()-1, y());
            if(y1 > y2)
                setPos(x(), y()+1);
            if(y1 < y2)
                setPos(x(), y()-1);
        }
        else if(y1 != y2){
            if(y1 > y2)
                setPos(x(), y()+1);
            if(y1 < y2)
                setPos(x(), y()-1);
        }
    }
    else{
        direction = 0;
        setPixmap(pixmap_left);
        if(distance > 300){
            if(x1 > x2)
                setPos(x()+1, y());
            if(x1 < x2)
                setPos(x()-1, y());
            if(y1 > y2)
                setPos(x(), y()+1);
            if(y1 < y2)
                setPos(x(), y()-1);
        }
        else if(y1 != y2){
            if(y1 > y2)
                setPos(x(), y()+1);
            if(y1 < y2)
                setPos(x(), y()-1);
        }
    }
}

void Enemy::shoot()
{
    Bullet *bullet = new Bullet(this, player);
    scene()->addItem(bullet);
}

void Enemy::die()
{
    if(direction == 0){
        setPixmap(pixmap_dead_left);
        movement->stop();
        shooting->stop();
    }
    else{
        setPixmap(pixmap_dead_right);
        movement->stop();
        shooting->stop();
    }
    emit dead();
}

Enemy::~Enemy(){}
