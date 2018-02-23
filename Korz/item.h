#ifndef ITEM_H
#define ITEM_H

#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

class Item : public QGraphicsItem
{
public:
    Item();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool clicked;

};

#endif // ITEM_H
