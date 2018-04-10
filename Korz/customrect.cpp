#include "customrect.h"

CustomRect::CustomRect(Character *player, int type)
{
    this->type = type;
    this->player = player;
    //Timer used to update the rect to check for a collision with the player
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_rect()));
    timer->start(500);
}

QRectF CustomRect::boundingRect() const
{
    if(type == 1)
        return QRectF(0, 0, 50, 50);
    else
        return QRectF(0, 0, 10, 20);
}

void CustomRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    if(type == 1){
        QBrush green_brush(Qt::green);
        painter->fillRect(bounds, green_brush);
    }
    else{
        QBrush white_brush(Qt::white);
        painter->fillRect(bounds, white_brush);
    }
}

void CustomRect::update_rect(){
    for(int x = 0; x < player->collidingItems().size(); x++){
        if(player->collidingItems().at(x) == this){
            emit destroyed();
            delete this;
        }
    }
}

CustomRect::~CustomRect(){}

