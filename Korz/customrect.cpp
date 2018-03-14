#include "customrect.h"



CustomRect::CustomRect()
{
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

CustomRect::~CustomRect(){

}

