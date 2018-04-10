#ifndef MEDKIT_H
#define MEDKIT_H
#include "item.h"

class Medkit : public Item
{
public:
    Medkit();
    Medkit(int, QString, int);
    int get_id() const;
    QString get_name() const;
    bool compare_medkits(Medkit*);
    int get_health() const;
    ~Medkit(); //This is necessary as Medkit is derived from item. It makes sure the top destructor is called
private:
    int id;
    QString name;
    int health;
    //Overloading = operator to check if two items are the same
    bool operator=(Medkit *b) {
        bool result;
        if(this->get_id() == b->get_id())
            result = true;
        else
            result = false;

        return result;
    }
};

#endif // MEDKIT_H
