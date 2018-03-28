#include "customrect.h"

CustomRect::CustomRect(Character *player)
{
    this->player = player;
    //Timer used to update the rect to check for a collision with the player
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update_rect()));
    timer->start(500);
}

QRectF CustomRect::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void CustomRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QPen black_pen(Qt::black);
    QBrush green_brush(Qt::green);
    painter->fillRect(bounds, green_brush);
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

