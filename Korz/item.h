#ifndef ITEM_H
#define ITEM_H

#include <QtGui>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QString>

//Overriding '==' operator REMOVE LATER -> New idea: Use when check if two items in inventory are the same by checking IDs
/*bool CustomRect::operator==(CustomRect& check)
{
    if(this->x() == check.x() && this->y() == check.y())
    {
        return true;
    }
    return false;
}*/

//Abstract class acting as a base for other items such as weapons & medkits
class Item
{
public:
    Item();
    virtual int get_id() = 0;
    virtual QString get_name() = 0;

private:
    int id;
    QString name;


};

#endif // ITEM_H
