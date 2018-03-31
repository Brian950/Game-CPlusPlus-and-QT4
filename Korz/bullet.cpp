#include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(Character *parent)
{
    type = 0;
    damage = parent->get_current_weapon()->get_damage();
    speed = parent->get_guns();
    direction = parent->get_direction();
    if(direction == 1){
        pixmap = QPixmap(":/Icons/bullet.png");
    }
    else{
        pixmap = QPixmap(":/Icons/bullet_left.png");
    }
    setPixmap(pixmap);
    setScale(0.09);
    if(direction == 0)
        setPos(parent->x()-28, parent->y()+13);
    else
        setPos(parent->x()+95, parent->y()+13);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

Bullet::Bullet(Enemy *parent, Character *play)
{
    player = play;
    type = 1;
    damage = parent->get_damage();
    speed = parent->get_fire_rate();
    direction = parent->get_direction();
    if(direction == 1){
        pixmap = QPixmap(":/Icons/bullet.png");
    }
    else{
        pixmap = QPixmap(":/Icons/bullet_left.png");
    }
    setScale(0.2);
    setPixmap(pixmap);
    if(direction == 0)
        setPos(parent->x()-20, parent->y()-20);
    else
        setPos(parent->x()+20, parent->y()-20);
}

int Bullet::get_damage()
{
    return damage;
}

void Bullet::move(){

    if(direction == 0)
        this->setPos(x()-speed, y());
    else
        this->setPos(x()+speed, y());

    QList<QGraphicsItem*> collisions = collidingItems();
    if(type == 1){
        for(int x = 0; x < collisions.length(); x++){
            if(collisions.at(x) == player){
                player->hit(damage);
                delete this;
            }
        }
    }
    //else

    if(x() > 950 || x() < -50)
        delete this;
}

Bullet::~Bullet(){}
