#ifndef ITEM_H
#define ITEM_H

#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QString>

//Abstract class acting as a base for other items such as weapons & medkits
class Item
{
public:
    Item();
    virtual int get_id() const = 0;
    virtual QString get_name() const = 0;
    virtual ~Item() = 0;
private:
    int id;
    QString name;


};

#endif // ITEM_H
