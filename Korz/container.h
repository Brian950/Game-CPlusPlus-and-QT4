#ifndef CONTAINER_H
#define CONTAINER_H
#include <QString>
#include <QGraphicsPixmapItem>
#include <QtMath>

class Container : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    int type;
    QString contents;
    QString generate_items(int& seed);
    QString generate_items();
public:
    Container();
    Container(int type, QWidget *parent);
    Container(int type, QWidget *parent, int seed);
    Container(int type, QString contents, QWidget *parent);
    int get_type() const;
    QString get_contents() const;
    void remove_item(int);
    int add_item(int);
    QPixmap pixmap;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ~Container();
signals:
    void open_inventory(QString, Container*);
};

#endif // CONTAINER_H
