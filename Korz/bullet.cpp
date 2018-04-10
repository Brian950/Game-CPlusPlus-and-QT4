 #include "bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(Character *parent, QList<Enemy*> *enemies)
{
    type = 0;
    damage = parent->get_current_weapon()->get_damage();
    speed = parent->get_guns()+2;
    direction = parent->get_direction();
    active_enemies = enemies;
    if(direction == 1){
        pixmap = QPixmap(":/Icons/bullet.png");
    }
    else{
        pixmap = QPixmap(":/Icons/bullet_left.png");
    }
    setPixmap(pixmap);
    setScale(0.09);
    if(direction == 0)
        setPos(parent->x()-50, parent->y()+13);
    else
        setPos(parent->x()+135, parent->y()+13);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

Bullet::Bullet(Enemy *parent, Character *play)
{
    player = play;
    type = 1;
    damage = parent->get_damage();
    speed = 3;
    direction = parent->get_direction();
    if(parent->get_type() != 3){
        enemy_type = 1;
        if(direction == 1){
            pixmap = QPixmap(":/Icons/enemy_bullet.png");
        }
        else{
            pixmap = QPixmap(":/Icons/enemy_bullet_left.png");
        }
    }
    else{
        enemy_type = 3;
        if(direction == 1){
            pixmap = QPixmap(":/Icons/missile.png");
        }
        else{
            pixmap = QPixmap(":/Icons/missile_left.png");
        }
    }

    setScale(0.09);
    setPixmap(pixmap);
    if(direction == 0)
        setPos(parent->x()-50, parent->y());
    else
        setPos(parent->x()+130, parent->y());

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

int Bullet::get_damage() const
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
        bool player_hit = false;
        bool object_hit = false;
        for(int x = 0; x < collisions.length(); x++){
            if(collisions.at(x) == player){
                player->hit(damage, enemy_type);
                player_hit = true;
            }
            else
                object_hit = true;
        }
        if(player_hit == true)
            delete this;
        else if(object_hit)
            delete this;
    }
    else{
        bool hit = false;
        qDebug() << "active_enemies: " << active_enemies->length();
        for(int x = 0; x < collisions.length(); x++){
            for(int y = 0; y < active_enemies->length(); y++){
                if(collisions.at(x) == active_enemies->at(y)){
                    active_enemies->at(y)->hit(damage);
                    hit = true;
                }
            }
            hit = true;
        }
        if(hit == true){
            delete this;
        }
    }

    if(x() > 950 || x() < -70)
        delete this;
}

Bullet::~Bullet(){}
