#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <QGraphicsPixmapItem>
#include "character.h"

class Container : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int type;
    QString contents;
public:
    Container();
    Container(int type, Character *player);
    Container(int type, Character *player, QString contents);
    int get_type();
    QString get_contents();
    QString generate_items();
    QPixmap pixmap;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ~Container();
signals:
    void open_inventory();
};

#endif // CONTAINER_H
