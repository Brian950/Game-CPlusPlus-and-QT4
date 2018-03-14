#ifndef CUSTOMRECT_H
#define CUSTOMRECT_H

#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

class CustomRect : public QGraphicsItem
{
public:
    CustomRect();
    ~CustomRect();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:

};

#endif // CUSTOMRECT_H
