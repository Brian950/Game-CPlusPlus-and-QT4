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

void MainMenu::on_north_button_clicked()
{

}

void MainMenu::on_south_button_clicked()
{

}

void MainMenu::on_east_button_clicked()
{

}

void MainMenu::on_west_button_clicked()
{

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
                    ui->active_weapon_label->setText("Active Weapon\n\nold rifle");
                    break;
            }
            case 2:{
                Weapon *bolt_rifle = new Weapon(2, "bolt rifle", 50, 1.5);
                player->set_current_weapon(bolt_rifle);
                ui->active_weapon_label->setText("Active Weapon\n\nbolt rifle");
                break;
            }
            case 3:{
                Weapon *assault_rifle = new Weapon(3, "assault rifle", 25, 0.25);
                player->set_current_weapon(assault_rifle);
                ui->active_weapon_label->setText("Active Weapon\n\nassault rifle");
                break;
            }
            case 4:{
                if(player->get_health() != 100){
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
                if(player->get_health() != 100){
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
                if(player->get_health() != 100){
                    Medkit *full = new Medkit(6, "full medkit", 100);
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
    story_thread->start();
}

void MainMenu::tutorial_part_2(){
    Container *tut_cont_1 = new Container(1, player, this);
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
    QPoint enemy_pos = QPoint(920, 10);
    spawn_enemy(1, enemy_pos);
}

void MainMenu::spawn_enemy(int type, QPoint position){
    QPoint pos2 = QPoint(920, 200);
    Enemy *enemy = new Enemy(type, player, position);
    tutorial_scene->addItem(enemy);
    active_enemy_list->append(enemy);
    connect(enemy, SIGNAL(dead()), this, SLOT(on_tutorial_enemy_dead()));
}

void MainMenu::on_tutorial_enemy_dead()
{
    tutorial_part_4();
}
