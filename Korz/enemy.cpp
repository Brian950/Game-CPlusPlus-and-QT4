#include "enemy.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int t, Character *player)
{
    type == t;
    if(player->x() > x()){
        direction = 1;
        //code to set right facing pixmap
    }
    else{
        direction = 0;
        //code to set left facing pixmap
    }
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

}

void Enemy::shoot()
{

}

void Enemy::die()
{

}

Enemy::~Enemy(){}
