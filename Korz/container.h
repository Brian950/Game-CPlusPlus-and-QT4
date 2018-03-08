#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <QGraphicsPixmapItem>

class Container : public QGraphicsPixmapItem
{
private:
    int type;
    QString contents;
public:
    Container();
    Container(int type);
    Container(int type, QString contents);
    int get_type();
    QString get_contents();
    QString generate_items();
    QPixmap pixmap;
    ~Container();
};

#endif // CONTAINER_H
