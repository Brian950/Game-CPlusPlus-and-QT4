#ifndef ROOM_H
#define ROOM_H
#include <QGraphicsScene>


class Room
{
public:
    Room();
    Room(int x);
private:
    QGraphicsScene *scene;
};

#endif // ROOM_H
