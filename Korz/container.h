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
    int player_luck;
    QString contents;
    QString generate_items(int& seed);
    QString generate_items();
public:
    Container();
    Container(int type, int player_luck, QWidget *parent);
    Container(int type, int player_luck, QWidget *parent, int seed);
    Container(int type, int player_luck, QString contents, QWidget *parent);
    int get_type() const;
    QString get_contents() const;
    void remove_item(int);
    int add_item(int);
    QPixmap pixmap;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    ~Container();
signals:
    void open_inventory(QString, Container*);

public slots:
    void clean_up();
};

#endif // CONTAINER_H
