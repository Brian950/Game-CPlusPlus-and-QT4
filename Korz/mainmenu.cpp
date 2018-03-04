#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QStyle>
#include <QDesktopWidget>

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    //this->showFullScreen();

    QString ability_default="None Selected";
    QString ability_crackshot="Crackshot: Deal a devastating ranged blow. (Cooldown 200s)";
    QString ability_beserker="Beserker: Take no damage and do double for 30s. (Cooldown 200s)";
    QString ability_ghost="Ghost: Remain unseen by enemies for 60s. (Cooldown 200s)";
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


    /*compass = new QGraphicsScene(this);
    ui->compass_view->setScene(compass);
    QPen black_pen(Qt::black);
    QBrush grey_brush(Qt::gray);
    compassX = compass->addRect(-20, 17, 100, 5, black_pen, grey_brush);
    compassX = compass->addRect(22, -20, 5, 100, black_pen, grey_brush);
    north_rect = compass->addRect(5, -47, 40, 40, black_pen, grey_brush);
    south_rect = compass->addRect(5, 47, 40, 40, black_pen, grey_brush);
    west_rect = compass->addRect(-40, 0, 40, 40, black_pen, grey_brush);
    east_rect = compass->addRect(50, 0, 40, 40, black_pen, grey_brush);
    north_text = compass->addText("N");
    south_text = compass->addText("S");
    west_text = compass->addText("W");
    east_text = compass->addText("E");
    north_text->setPos(16, -40);
    south_text->setPos(17, 55);
    west_text->setPos(-31, 8);
    east_text->setPos(61, 8);*/
    room_scene = new QGraphicsScene(this);
    room_scene->setSceneRect(-500, -250, 1000, 600);
    room_scene->setFocus();
    ui->game_view->setScene(room_scene);
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
        Character *player = new Character(CHARACTER_NAME, STR_LAST_VALUE, SPD_LAST_VALUE, GUN_LAST_VALUE, LCK_LAST_VALUE, ui->ability_box->currentIndex());
        DB_Controller *dbc = new DB_Controller("/home/brian/Korz/trunk/Korz/kroz.db");
        start_tutorial(player);
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

void MainMenu::start_tutorial(Character *player)
{
    ui->stackedWidget->setCurrentIndex(2);
    player->setRect(-400, 0, 10, 100);
    player->setFocus();
    room_scene->addItem(player);
}




void MainMenu::on_pushButton_3_clicked()
{
    Character *player = new Character("Brian", 5, 5, 5, 5, 1);
    DB_Controller *dbc = new DB_Controller("/home/brian/Korz/trunk/Korz/kroz.db");
    dbc->add_player(player->get_name(), player->get_strength(), player->get_speed(), player->get_guns(), player->get_luck(), player->get_special());
    start_tutorial(player);
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
