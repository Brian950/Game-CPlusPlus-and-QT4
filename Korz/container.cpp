#include "container.h"
#include "character.h"
#include <QDebug>

Container::Container()
{
}

Container::Container(int type, int player_luck, QWidget *parent){
    this->type = type;
    contents = generate_items();
    this->player_luck = player_luck;

    if(type == 1)
        pixmap = QPixmap(":/Icons/wooden_crate.png");
    if(type == 2)
        pixmap = QPixmap(":/Icons/trak2_panel2c.tga");

    setPixmap(pixmap);
    setScale(0.3);
    connect(this, SIGNAL(open_inventory(QString, Container*)), parent, SLOT(open_inventory(QString, Container*)));
    connect(parent, SIGNAL(clean_up()), this, SLOT(clean_up()));
}

Container::Container(int type, int player_luck, QWidget *parent, int seed){
    this->type = type;

    //Reference example
    int& seed_ref = seed;
    this->player_luck = player_luck;
    contents = generate_items(seed_ref);

    if(type == 1)
        pixmap = QPixmap(":/Icons/wooden_crate.png");
    if(type == 2)
        pixmap = QPixmap(":/Icons/trak2_panel2c.tga");

    setPixmap(pixmap);
    setScale(0.3);
    connect(this, SIGNAL(open_inventory(QString, Container*)), parent, SLOT(open_inventory(QString, Container*)));
}


Container::Container(int type, int player_luck, QString contents, QWidget *parent)
{
    this->type = type;
    this->contents = contents;
    this->player_luck = player_luck;

    if(type == 1)
        pixmap = QPixmap(":/Icons/wooden_crate.png");
    if(type == 2)
        pixmap = QPixmap(":/Icons/trak2_panel2c.tga");

    setPixmap(pixmap);
    setScale(0.3);
    connect(this, SIGNAL(open_inventory(QString, Container*)), parent, SLOT(open_inventory(QString, Container*)));
}

void Container::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit open_inventory(contents, this);
}

QString Container::generate_items(){
    QString item_list = "";

    srand(time(0)); //sets seed for rand
    int rand_num_of_items = rand() % 2 + 1;
    int rand_item_range;
    int max_of_range = 100 - (player_luck*2);
    for(int x = 0; x < rand_num_of_items; x++){
        rand_item_range = rand() % max_of_range + 1;
        if(rand_item_range < 5){//assault rifle
            if(x == 0){
                item_list.append(QString::number(3));
            }
            else{
                item_list.append(":"+QString::number(3));
            }
        }
        else if(rand_item_range < 10){//full medkit
            if(x == 0){
                item_list.append(QString::number(6));
            }
            else{
                item_list.append(":"+QString::number(6));
            }
        }
        else if(rand_item_range < 20){//bolt rifle
            if(x == 0){
                item_list.append(QString::number(2));
            }
            else{
                item_list.append(":"+QString::number(2));
            }
        }
        else if(rand_item_range < 40){//Medium medkit
            if(x == 0){
                item_list.append(QString::number(5));
            }
            else{
                item_list.append(":"+QString::number(5));
            }
        }
        else if(rand_item_range < 70){//Old rifle
            if(x == 0){
                item_list.append(QString::number(1));
            }
            else{
                item_list.append(":"+QString::number(1));
            }
        }
        else if(rand_item_range < 100){//small medkit
            if(x == 0){
                item_list.append(QString::number(4));
            }
            else{
                item_list.append(":"+QString::number(4));
            }
        }
    }
    return item_list;
}

QString Container::generate_items(int& seed){
    QString item_list = "";

    srand(time(0)+seed); //sets seed for rand
    int rand_num_of_items = rand() % 2 + 1;
    int rand_item_range;
    int max_of_range = 100 - (player_luck*2);
    for(int x = 0; x < rand_num_of_items; x++){
        rand_item_range = rand() % max_of_range + 1;
        if(rand_item_range < 5){//assault rifle
            if(x == 0){
                item_list.append(QString::number(3));
            }
            else{
                item_list.append(":"+QString::number(3));
            }
        }
        else if(rand_item_range < 10){//full medkit
            if(x == 0){
                item_list.append(QString::number(6));
            }
            else{
                item_list.append(":"+QString::number(6));
            }
        }
        else if(rand_item_range < 20){//bolt rifle
            if(x == 0){
                item_list.append(QString::number(2));
            }
            else{
                item_list.append(":"+QString::number(2));
            }
        }
        else if(rand_item_range < 40){//Medium medkit
            if(x == 0){
                item_list.append(QString::number(5));
            }
            else{
                item_list.append(":"+QString::number(5));
            }
        }
        else if(rand_item_range < 70){//Old rifle
            if(x == 0){
                item_list.append(QString::number(1));
            }
            else{
                item_list.append(":"+QString::number(1));
            }
        }
        else if(rand_item_range < 100){//small medkit
            if(x == 0){
                item_list.append(QString::number(4));
            }
            else{
                item_list.append(":"+QString::number(4));
            }
        }
    }
    return item_list;
}


void Container::remove_item(int id)
{
    QStringList item_list = contents.split(":");
    if(item_list.length() > 0){
        bool removed = false;
        for(int x = 0; x < item_list.length(); x++){
            if(!removed){
                if(item_list.at(x).toInt() == id){
                    item_list.removeAt(x);
                    removed = true;
                }
            }
        }
    }

    if(item_list.length() == 0){
        contents = "";
    }
    else{
        for(int x = 0; x < item_list.length(); x++){
            if(x == 0){
                contents = item_list.at(x);
            }
            else{
                contents.append(":"+item_list.at(x));
            }
        }
    }
}

int Container::add_item(int id)
{
    QStringList item_list = contents.split(":");
    if(contents.length() == 0){
        contents = QString::number(id);
        return 0;
    }
    else if(contents.length() == 1){
        contents.append(":"+QString::number(id));
        return 0;
    }
    else if(item_list.length() < 10){
        contents.append(":"+QString::number(id));
        return 0;
    }
    else{
        return 1;
    }
}

QString Container::get_contents() const{
    return contents;
}

int Container::get_type() const{
    return type;
}

void Container::clean_up()
{
    delete this;
}

Container::~Container(){}

