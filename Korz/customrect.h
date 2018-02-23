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
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool clicked;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMRECT_H
