#include "mainmenu.h"
#include "ui_mainmenu.h"

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    dbc = new DB_Controller("/home/brian/Korz/trunk/Korz/kroz.db");//Initialises sqlite3 database
    //this->showFullScreen();

    QString ability_default="None Selected";
    QString ability_crackshot="Crackshot: Deal a devastating ranged blow. (Cooldown 60s)";
    QString ability_beserker="Beserker: Take no damage and do double for 30s. (Cooldown 60s)";
    QString ability_ghost="Ghost: Remain unseen by enemies for 30s. (Cooldown 60s)";
    ui->ability_box->addItem(ability_default);
    ui->ability_box->addItem(ability_crackshot);
    ui->ability_box->addItem(ability_beserker);
    ui->ability_box->addItem(ability_ghost);
    ui->strength_value->setButtonSymbols(QSpinBox::PlusMinus);
    ui->speed_value->setButtonSymbols(QSpinBox::PlusMinus);
    ui->guns_value->setButtonSymbols(QSpinBox::PlusMinus);
    ui->luck_value->setButtonSymbols(QSpinBox::PlusMinus);

    ui->points_label->setNum(CHARACTER_POINTS);

    //Character attributes Signals/Slots
    connect(ui->strength_value, SIGNAL(valueChanged(int)), this, SLOT(strength_value(int)));
    connect(ui->speed_value, SIGNAL(valueChanged(int)), this, SLOT(speed_value(int)));
    connect(ui->guns_value, SIGNAL(valueChanged(int)), this, SLOT(guns_value(int)));
    connect(ui->luck_value, SIGNAL(valueChanged(int)), this, SLOT(luck_value(int)));
    //Progress bar updates
    connect(ui->name_edit, SIGNAL(editingFinished()), this, SLOT(update_progress(int)));

    active_enemy_list = new QList<Enemy*>();
    tutorial_scene = new QGraphicsScene(this);
    tutorial_scene->setSceneRect(-50, -250, 1000, 600);
    tutorial_scene->setFocus();
    ui->game_view->setScene(tutorial_scene);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_back_button_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    on_reset_button_clicked();
}

void MainMenu::set_attribute_value(int x, int attribute)
{
    int attr;
    switch(attribute){
        case 0:
            attr = STR_LAST_VALUE;
            break;
        case 1:
            attr = SPD_LAST_VALUE;
            break;
        case 2:
            attr = GUN_LAST_VALUE;
            break;
        case 3:
            attr = LCK_LAST_VALUE;
            break;
    }

    if(x > attr){
        CHARACTER_POINTS--;
        switch(attribute){
            case 0:
                STR_LAST_VALUE = x;
                break;
            case 1:
                SPD_LAST_VALUE = x;
                break;
            case 2:
                GUN_LAST_VALUE = x;
                break;
            case 3:
                LCK_LAST_VALUE = x;
                break;
        }
        ui->points_label->setNum(CHARACTER_POINTS);
        if(CHARACTER_POINTS >= 0)
            update_progress(3);
    }
    else if(x < attr)
    {
        CHARACTER_POINTS++;
        ui->points_label->setNum(CHARACTER_POINTS);
        switch(attribute){
            case 0:
                STR_LAST_VALUE = x;
                break;
            case 1:
                SPD_LAST_VALUE = x;
                break;
            case 2:
                GUN_LAST_VALUE = x;
                break;
            case 3:
                LCK_LAST_VALUE = x;
                break;
        }
        if(CHARACTER_POINTS > 0)
            update_progress(-3);
    }
    //Checks points value and changes text to red if it falls bellow 0.
    if(CHARACTER_POINTS < 0)
        ui->points_label->setStyleSheet("color:red;");
    else
        ui->points_label->setStyleSheet("color:white;");
}

void MainMenu::strength_value(int x)
{
    set_attribute_value(x, 0);
}

void MainMenu::speed_value(int x)
{
    set_attribute_value(x, 1);
}

void MainMenu::guns_value(int x)
{
    set_attribute_value(x, 2);
}

void MainMenu::luck_value(int x)
{
    set_attribute_value(x, 3);
}

void MainMenu::update_progress(int x)
{
    ui->character_progress->setValue(ui->character_progress->value()+x);
}

void MainMenu::on_name_edit_editingFinished()
{
    if(ui->name_edit->text().size() < 1){
        name_set = 0;
        if(CHARACTER_POINTS > 0)
            ui->character_progress->setValue(ui->character_progress->value() - 20);
    }
    else{
        CHARACTER_NAME = ui->name_edit->text();
        if(name_set != 1)
            ui->character_progress->setValue(ui->character_progress->value() + 20);

        name_set = 1;
    }
}

void MainMenu::on_ability_box_currentIndexChanged(int index)
{
    if(index != 0 && special_set == 0){
        update_progress(20);
        special_set = 1;
    }
    else if(index == 0 && special_set == 1){
        update_progress(-20);
        special_set = 0;
    }
}

void MainMenu::on_finish_button_clicked()
{
    if(ui->character_progress->value() == 100 && CHARACTER_POINTS == 0){
        player = new Character(CHARACTER_NAME, STR_LAST_VALUE, SPD_LAST_VALUE, GUN_LAST_VALUE, LCK_LAST_VALUE, ui->ability_box->currentIndex(), active_enemy_list);
        ui->health_bar->setMaximum(player->get_health());
        ui->health_bar_2->setMaximum(player->get_health());
        ui->health_bar->setValue(player->get_health());
        ui->health_bar_2->setValue(player->get_health());
        connect(player, SIGNAL(update_health()), this, SLOT(update_health_bar()));
        int character_id = dbc->number_of_characters()+1;
        int insert_char_result = dbc->add_player(character_id, player->get_name(), player->get_strength(), player->get_speed(), player->get_guns(), player->get_luck(), player->get_special(), player->get_location(),player->get_health(), player->get_inventory());
        if(insert_char_result == 1){
            QMessageBox msgBox;
            msgBox.setText("This name is already taken.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
        else{
            tutorial_part_1();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Character Incomplete!\nMake sure you only assign 20 character points and have given your character a name and special ability.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainMenu::on_reset_button_clicked()
{
    ui->character_progress->setValue(0);
    ui->strength_value->setValue(0);
    ui->speed_value->setValue(0);
    ui->guns_value->setValue(0);
    ui->luck_value->setValue(0);
    CHARACTER_POINTS = 20;
    ui->points_label->setText("20");
    ui->points_label->setStyleSheet("color:white;");
    name_set = 0;
    special_set = 0;
    ui->name_edit->setText("");
    ui->ability_box->setCurrentIndex(0);
}

void MainMenu::update_story(QString story_text)
{
    ui->story_label->setText(story_text);
}

void MainMenu::on_pushButton_3_clicked()
{
    player = new Character("Brian", 5, 10, 5, 5, 1, active_enemy_list);
    ui->health_bar->setMaximum(player->get_health());
    ui->health_bar_2->setMaximum(player->get_health());
    ui->health_bar->setValue(player->get_health());
    ui->health_bar_2->setValue(player->get_health());
    connect(player, SIGNAL(update_health()), this, SLOT(update_health_bar()));
    dbc->clear_character_table();
    int character_id = dbc->number_of_characters()+1;
    int insert_char_result = dbc->add_player(character_id, player->get_name(), player->get_strength(), player->get_speed(), player->get_guns(), player->get_luck(), player->get_special(), player->get_location(),player->get_health(), player->get_inventory());
    if(insert_char_result == 1){
        QMessageBox msgBox;
        msgBox.setText("This name is already taken.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
    else{
        tutorial_part_1();
    }
}

void MainMenu::open_inventory(QString container, Container *act_cont){
    player->setFocus();
    QString inventory = player->get_inventory();
    active_container = act_cont;
    ui->stackedWidget->setCurrentIndex(3);

    int item_id;
    QString item_name;
    QListWidgetItem *list_item;

    ui->player_inventory->clear();
    ui->external_inventory->clear();
    int inv_size = player->get_inventory_size();
    QString inv_stat("("); inv_stat+=QString::number(inv_size); inv_stat+="/10)";
    ui->inventory_status_label->setText(inv_stat);

    //populates the player inventory list
    QStringList inventory_items = inventory.split(":");
    if(inventory_items.length() > 0 && inventory != ""){
        for(int x = 0; x < inventory_items.length();x++){
            item_id = inventory_items.at(x).toInt();
            item_name = dbc->get_item_name(item_id);
            list_item = new QListWidgetItem();
            list_item->setText(item_name);
            ui->player_inventory->addItem(list_item);
        }
    }
    else if(inventory.length() == 1 && inventory != ""){
        item_id = inventory.toInt();
        item_name = dbc->get_item_name(item_id);
        list_item = new QListWidgetItem();
        list_item->setText(item_name);
        ui->player_inventory->addItem(list_item);
    }

    //populates the container list
    QStringList container_items = container.split(":");
    if(container_items.length() > 0 && container != ""){
        for(int x = 0; x < container_items.length(); x++){
            item_id = container_items.at(x).toInt();
            item_name = dbc->get_item_name(item_id);
            list_item = new QListWidgetItem();
            list_item->setText(item_name);
            ui->external_inventory->addItem(list_item);
        }
    }
    else if(container_items.length() == 1 && container != ""){
        item_id = container.toInt();
        item_name = dbc->get_item_name(item_id);
        list_item = new QListWidgetItem();
        list_item->setText(item_name);
        ui->external_inventory->addItem(list_item);
    }
}

void MainMenu::mousePressEvent(QMouseEvent *event)
{
    if(player != NULL){
        QList<QGraphicsItem*> items = ui->game_view->items();
        for(int x = 0; x < items.length(); x++){
            if(items.at(x) == player)
                player->setFocus();
        }
    }
}

void MainMenu::on_inventory_back_button_clicked()
{
    if(tut_cont_first_time && story_thread->part_2_complete == true){
        tut_cont_first_time = false;
        tutorial_part_3();
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void MainMenu::on_add_to_inventory_button_clicked()
{
    if(player->get_inventory_size() < 10){
        if(ui->external_inventory->currentItem() != NULL){
            QListWidgetItem *item = ui->external_inventory->takeItem(ui->external_inventory->currentRow());
            ui->player_inventory->addItem(item);
            int item_id = dbc->get_item_id(item->text());
            player->add_item_to_inventory(item_id);
            active_container->remove_item(item_id);
            QString inv_stat("("); inv_stat+=QString::number(player->get_inventory_size()); inv_stat+="/10)";
            ui->inventory_status_label->setText(inv_stat);
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Inventory full, drop items to free up space.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
    }
}

void MainMenu::on_remove_from_inventory_button_clicked()
{
    if(ui->player_inventory->currentItem() != NULL){
        QListWidgetItem *item = ui->player_inventory->takeItem(ui->player_inventory->currentRow());
        ui->external_inventory->addItem(item);

        int item_id = dbc->get_item_id(item->text());
        player->remove_item_from_inventory(item_id);
        active_container->add_item(item_id);
        QString inv_stat("("); inv_stat+=QString::number(player->get_inventory_size()); inv_stat+="/10)";
        ui->inventory_status_label->setText(inv_stat);
    }
}

void MainMenu::on_inventory_button_clicked()
{
    QString inventory = player->get_inventory();
    ui->main_inventory->clear();
    QString item_name;
    QListWidgetItem *list_item;
    int item_id;
    QStringList inventory_items = inventory.split(":");
    if(inventory_items.length() > 0 && inventory != ""){
        for(int x = 0; x < inventory_items.length();x++){
            item_id = inventory_items.at(x).toInt();
            item_name = dbc->get_item_name(item_id);
            list_item = new QListWidgetItem();
            list_item->setText(item_name);
            ui->main_inventory->addItem(list_item);
        }
    }
    else if(inventory.length() == 1 && inventory != ""){
        item_id = inventory.toInt();
        item_name = dbc->get_item_name(item_id);
        list_item = new QListWidgetItem();
        list_item->setText(item_name);
        ui->main_inventory->addItem(list_item);
    }
    ui->stackedWidget->setCurrentIndex(4);

}

void MainMenu::on_main_inventory_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->game_view->setFocus();
    tutorial_scene->setFocus();
    player->setFocus();
}

void MainMenu::on_use_item_button_clicked()
{
    if(ui->main_inventory->currentItem() != NULL){
        QListWidgetItem *item = ui->main_inventory->currentItem();
        int item_id = dbc->get_item_id(item->text());
            switch(item_id){
                case 1:{
                    Weapon *old_rifle = new Weapon(1, "old rifle", 10, 1);
                    player->set_current_weapon(old_rifle);
                    ui->active_weapon_label->setText("Active Weapon\n-------------------------\nOld Rifle\n\nDamage: 10");
                    break;
            }
            case 2:{
                Weapon *bolt_rifle = new Weapon(2, "bolt rifle", 50, 1.5);
                player->set_current_weapon(bolt_rifle);
                ui->active_weapon_label->setText("Active Weapon\n-------------------------\nBolt Rifle\n\nDamage: 50");
                break;
            }
            case 3:{
                Weapon *assault_rifle = new Weapon(3, "assault rifle", 25, 0.5);
                player->set_current_weapon(assault_rifle);
                ui->active_weapon_label->setText("Active Weapon\n-------------------------\nAssault Rifle\n\nDamage: 25");
                break;
            }
            case 4:{
                if(player->get_health() != player->get_max_health()){
                    Medkit *small = new Medkit(4, "small medkit", 25);
                    player->use_medkit(small);
                    ui->health_bar->setValue(player->get_health());
                    ui->health_bar_2->setValue(player->get_health());
                    QListWidgetItem *item = ui->main_inventory->currentItem();
                    player->remove_item_from_inventory(4);
                    delete item;
                    delete small;
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setText("Your health is already full!");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                }
                break;
            }
            case 5:{
                if(player->get_health() != player->get_max_health()){
                    Medkit *medium = new Medkit(5, "medium medkit", 50);
                    player->use_medkit(medium);
                    ui->health_bar->setValue(player->get_health());
                    ui->health_bar_2->setValue(player->get_health());
                    QListWidgetItem *item = ui->main_inventory->currentItem();
                    player->remove_item_from_inventory(5);
                    delete item;
                    delete medium;
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setText("Your health is already full!");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                }
                break;
            }
            case 6:{
                if(player->get_health() != player->get_max_health()){
                    Medkit *full = new Medkit(6, "full medkit", player->get_max_health());
                    player->use_medkit(full);
                    ui->health_bar->setValue(player->get_health());
                    ui->health_bar_2->setValue(player->get_health());
                    player->remove_item_from_inventory(6);
                    QListWidgetItem *item = ui->main_inventory->currentItem();
                    delete item;
                    delete full;
                }
                else{
                    QMessageBox msgBox;
                    msgBox.setText("Your health is already full!");
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.exec();
                }
                break;
            }
        }
    }
}

void MainMenu::update_health_bar()
{
    ui->health_bar->setValue(player->get_health());
    ui->health_bar_2->setValue(player->get_health());
}


//-----MISSION RELATED-----

void MainMenu::tutorial_part_1()
{
    ui->stackedWidget->setCurrentIndex(2);
    player->setFocus();
    player->setPos(50, 0);
    tutorial_scene->addItem(player);
    player->set_x_limit(300);
    story_thread = new StoryThread(this);
    connect(story_thread, SIGNAL(update_story(QString)),this, SLOT(update_story(QString)));
    connect(story_thread, SIGNAL(spawn_tutorial_rects()), this, SLOT(spawn_tutorial_rects()));
    connect(story_thread, SIGNAL(spawn_tutorial_enemy()), this, SLOT(spawn_tutorial_enemy()));
    connect(story_thread, SIGNAL(start_fight()), this, SLOT(start_fight()));
    story_thread->start();
}

void MainMenu::tutorial_part_2(){
    Container *tut_cont_1 = new Container(1, this);
    tut_cont_1->setPos(450, 100);
    tut_cont_1->setZValue(-1);
    tutorial_scene->addItem(tut_cont_1);
    story_thread->start();
}

void MainMenu::tutorial_part_3(){
    story_thread->start();
}

void MainMenu::tutorial_part_4(){
    story_thread->start();
}

void MainMenu::tutorial_part_5(){
    story_thread->start();
}

void MainMenu::tutorial_part_6(){
    story_thread->start();
}

void MainMenu::tutorial_part_7(){
    story_thread->start();
}

void MainMenu::spawn_tutorial_rects(){
    rect1 = new CustomRect(player);
    rect1->setPos(40, -120);
    rect1->setZValue(-1);
    tutorial_scene->addItem(rect1);
    rect2 = new CustomRect(player);
    rect2->setPos(40, 200);
    rect2->setZValue(-1);
    tutorial_scene->addItem(rect2);
    rect3 = new CustomRect(player);
    rect3->setPos(200, -120);
    rect3->setZValue(-1);
    tutorial_scene->addItem(rect3);
    rect4 = new CustomRect(player);
    rect4->setPos(200,200);
    rect4->setZValue(-1);
    tutorial_scene->addItem(rect4);
    //Rectangles for tutorial first task
    connect(rect1, SIGNAL(destroyed()), this, SLOT(rectangle_destroyed()));
    connect(rect2, SIGNAL(destroyed()), this, SLOT(rectangle_destroyed()));
    connect(rect3, SIGNAL(destroyed()), this, SLOT(rectangle_destroyed()));
    connect(rect4, SIGNAL(destroyed()), this, SLOT(rectangle_destroyed()));
}

//Once the four tutorial rects are destroyed, then the next task is triggered
void MainMenu::rectangle_destroyed(){
    tut_rect_counter++;
    if(tut_rect_counter == 4){
        player->set_x_limit(500);
        tutorial_part_2();
    }
}

void MainMenu::spawn_tutorial_enemy(){
    player->set_x_limit(900);
    QPoint enemy_pos = QPoint(920, 0);
    spawn_enemy(1, enemy_pos);
}

void MainMenu::spawn_enemy(int type, QPoint position){
    Enemy *enemy = new Enemy(type, player, position);
    tutorial_scene->addItem(enemy);
    active_enemy_list->append(enemy);
    connect(enemy, SIGNAL(dead()), this, SLOT(on_tutorial_enemy_dead()));
}

void MainMenu::on_tutorial_enemy_dead()
{
    if(!story_thread->part_4_complete)
        tutorial_part_4();
}

void MainMenu::start_fight(){
    Enemy *enemy1 = new Enemy(1, player, right_middle);
    //
    Enemy *enemy2 = new Enemy(2, player, right_top);
    Enemy *enemy3 = new Enemy(3, player, right_bottom);
    room_2_scene->addItem(enemy1);
    active_enemy_list->append(enemy1);
    room_2_scene->addItem(enemy2);
    active_enemy_list->append(enemy2);
    room_2_scene->addItem(enemy3);
    active_enemy_list->append(enemy3);
    connect(enemy1, SIGNAL(dead()), this, SLOT(fight_enemy_dead()));
    connect(enemy2, SIGNAL(dead()), this, SLOT(fight_enemy_dead()));
    connect(enemy3, SIGNAL(dead()), this, SLOT(fight_enemy_dead()));
}

void MainMenu::fight_enemy_dead(){
    fight_enemy_dead_counter++;
    if(fight_enemy_dead_counter == 3){
        Enemy *enemy = new Enemy(1, player, left_top);
        room_2_scene->addItem(enemy);
        active_enemy_list->append(enemy);
        connect(enemy, SIGNAL(dead()), this, SLOT(fight_enemy_dead()));
    }
    else if(fight_enemy_dead_counter == 4){
        tutorial_part_7();
    }
}



//Room setup
void MainMenu::room_1_setup(){
    room_1_scene = new QGraphicsScene(this);
    room_1_scene->setSceneRect(-50, -250, 1000, 600);
    room_1_scene->addItem(player);
    player->setPos(50, 0);
    Container *wooden_box1 = new Container(1, this, 4895);
    Container *wooden_box2 = new Container(1, this, 9987);
    Container *wooden_box3 = new Container(1, this, 1564);
    wooden_box1->setPos(600, 0);
    wooden_box2->setPos(100, 100);
    wooden_box3->setPos(800, -100);
    wooden_box1->setZValue(-1);
    wooden_box2->setZValue(-1);
    wooden_box3->setZValue(-1);
    room_1_scene->addItem(wooden_box1);
    room_1_scene->addItem(wooden_box2);
    room_1_scene->addItem(wooden_box3);
    ui->game_view->setFocus();
    room_1_scene->setFocus();
    player->setFocus();
    ui->game_view->setStyleSheet("border-Image:url(:/Rooms/room_1.png);");
}

void MainMenu::room_2_setup()
{
    room_2_scene = new QGraphicsScene(this);
    room_2_scene->setSceneRect(-50, -250, 1000, 600);
    room_2_scene->addItem(player);
    player->setPos(50, 0);
    Container *metal_box1 = new Container(2, this, 4895);
    Container *metal_box2 = new Container(2, this, 9987);
    Container *metal_box3 = new Container(2, this, 1564);
    Container *wooden_box1 = new Container(1, this, 9995);
    metal_box1->setPos(300, 100);
    metal_box2->setPos(800, 0);
    metal_box3->setPos(100, 50);
    wooden_box1->setPos(550, -100);
    metal_box1->setZValue(-1);
    metal_box2->setZValue(-1);
    metal_box3->setZValue(-1);
    wooden_box1->setZValue(-1);
    room_2_scene->addItem(metal_box1);
    room_2_scene->addItem(metal_box2);
    room_2_scene->addItem(metal_box3);
    room_2_scene->addItem(wooden_box1);
    ui->game_view->setFocus();
    room_1_scene->setFocus();
    player->setFocus();
    ui->game_view->setStyleSheet("border-Image:url(:/Rooms/room_2.png);");
}

//Directional Buttons
void MainMenu::on_north_button_clicked()
{

}

void MainMenu::on_south_button_clicked()
{

}

void MainMenu::on_east_button_clicked()
{
    if(!story_thread->part_5_complete){
        if(story_thread->part_4_complete){
            tutorial_scene->removeItem(player);
            room_1_setup();
            ui->game_view->setScene(room_1_scene);
            tutorial_part_5();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("You must complete the tutorial before leaving!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }
    else if(story_thread->part_5_complete && !story_thread->part_6_complete){
        room_1_scene->removeItem(player);
        room_2_setup();
        ui->game_view->setScene(room_2_scene);
        tutorial_part_6();
    }

}

void MainMenu::on_west_button_clicked()
{

}
