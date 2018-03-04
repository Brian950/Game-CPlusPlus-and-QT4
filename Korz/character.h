#ifndef CHARACTER_H
#define CHARACTER_H
#include <vector>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsRectItem>

using namespace std;

class Character : public QGraphicsRectItem
{
private:
    QString name;
    int strength;
    int speed;
    int guns;
    int luck;
    int special_ability;
    int location;
    int health;
    vector<int> inventory_array;
    QSet<int> pressedKeys;

public:
    Character();
    Character(QString, int, int, int, int, int);
    QString get_name();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void set_name(QString);
    int get_strength();
    void set_strength(int);
    int get_speed();
    void set_speed(int);
    int get_guns();
    void set_guns(int);
    int get_luck();
    void set_luck(int);
    int get_special();
    void set_special(int);
    int get_location();
    void set_location(int);
    int get_health();
    void set_health(int);
    vector<int> get_inventory();
    void set_inventory(vector<int>);

};

#endif // CHARACTER_H
