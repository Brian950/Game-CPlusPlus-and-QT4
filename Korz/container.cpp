#include "container.h"

Container::Container()
{
}

Container::Container(int type, Character *player){
    this->type = type;
    contents = generate_items();
    if(type == 1)
        pixmap = QPixmap(":/Icons/wooden_crate.png");

    setPixmap(pixmap);
    setScale(0.3);
}

Container::Container(int type, Character *player, QString contents)
{
    this->type = type;
    this->contents = contents;
}

void Container::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit open_inventory();
}

QString Container::generate_items(){
    QString item_list = "";

    //code to generate item list

    return item_list;
}

QString Container::get_contents(){
    return contents;
}

int Container::get_type(){
    return type;
}

Container::~Container(){}
