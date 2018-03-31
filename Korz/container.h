#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <QGraphicsPixmapItem>
#include "character.h"
#include <QtMath>

class Container : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int type;
    QString contents;
public:
    Container();
    Container(int type, Character *player, QWidget *parent);
    Container(int type, Character *player, QString contents, QWidget *parent);
    int get_type();
    QString get_contents();
    QString generate_items();
    Character *player;
    void remove_item(int);
    int add_item(int);
    QPixmap pixmap;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ~Container();
signals:
    void open_inventory(QString, Container*);
};

#endif // CONTAINER_H
