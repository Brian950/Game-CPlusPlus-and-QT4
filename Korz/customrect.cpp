#include "customrect.h"



CustomRect::CustomRect()
{
    clicked = false;
}

QRectF CustomRect::boundingRect() const
{
    return QRectF(0, 0, 100, 100);
}

void CustomRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QPen black_pen(Qt::black);
    QBrush grey_brush(Qt::gray);

    if(clicked){
        grey_brush.setColor(Qt::red);
    }
    painter->fillRect(bounds, grey_brush);
}

void CustomRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    clicked = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void CustomRect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    clicked = false;
    update(); //forces the object to paint
    QGraphicsItem::mousePressEvent(event);
}
