#ifndef CUSTOMRECT_H
#define CUSTOMRECT_H

#include <QtGui>
#include <QList>
#include <QGraphicsObject>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include "character.h"

class CustomRect : public QGraphicsObject
{
    Q_OBJECT
public:
    CustomRect(Character *player);
    virtual ~CustomRect();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:
    void update_rect();
private:
    bool deletable;
    Character *player;
protected:

signals:
    void destroyed();

};

#endif // CUSTOMRECT_H
