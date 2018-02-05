#include "mainmenu.h"
#include "ui_mainmenu.h"

int CHARACTER_POINTS = 20;
int STR_LAST_VALUE = 0, SPD_LAST_VALUE = 0, GUN_LAST_VALUE = 0, LCK_LAST_VALUE = 0;
int name_set = 0;
QString CHARACTER_NAME = "";


MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    QString ability_default="None Selected";
    QString ability_crackshot="Crackshot: Deal a devastating ranged blow. (Cooldown 200s)";
    QString ability_beserker="Beserker: Take no damage and do double for 30s. (Cooldown 200s)";
    QString ability_ghost="Ghost: Remain unseen by enemies for 60s. (Cooldown 200s)";
    ui->comboBox->addItem(ability_default);
    ui->comboBox->addItem(ability_crackshot);
    ui->comboBox->addItem(ability_beserker);
    ui->comboBox->addItem(ability_ghost);
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
    connect(ui->name_edit, SIGNAL(editingFinished()), this, SLOT(update_progress()))

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainMenu::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainMenu::strength_value(int x)
{
    if(x > STR_LAST_VALUE){
        CHARACTER_POINTS--;
        STR_LAST_VALUE = x;
        ui->points_label->setNum(CHARACTER_POINTS);
    }
    else if(x < STR_LAST_VALUE)
    {
        CHARACTER_POINTS++;
        ui->points_label->setNum(CHARACTER_POINTS);
        STR_LAST_VALUE = x;
    }
    //Checks points value and changes text to red if it falls bellow 0.
    if(CHARACTER_POINTS < 0)
        ui->points_label->setStyleSheet("color:red;");
    else
        ui->points_label->setStyleSheet("color:white;");
}

void MainMenu::speed_value(int x)
{
    if(x > SPD_LAST_VALUE){
        CHARACTER_POINTS--;
        SPD_LAST_VALUE = x;
        ui->points_label->setNum(CHARACTER_POINTS);
    }
    else if(x < SPD_LAST_VALUE)
    {
        CHARACTER_POINTS++;
        ui->points_label->setNum(CHARACTER_POINTS);
        SPD_LAST_VALUE = x;
    }

    if(CHARACTER_POINTS < 0)
        ui->points_label->setStyleSheet("color:red;");
    else
        ui->points_label->setStyleSheet("color:white;");
}

void MainMenu::guns_value(int x)
{
    if(x > GUN_LAST_VALUE){
        CHARACTER_POINTS--;
        GUN_LAST_VALUE = x;
        ui->points_label->setNum(CHARACTER_POINTS);
    }
    else if(x < GUN_LAST_VALUE)
    {
        CHARACTER_POINTS++;
        ui->points_label->setNum(CHARACTER_POINTS);
        GUN_LAST_VALUE = x;
    }

    if(CHARACTER_POINTS < 0)
        ui->points_label->setStyleSheet("color:red;");
    else
        ui->points_label->setStyleSheet("color:white;");
}

void MainMenu::luck_value(int x)
{
    if(x > LCK_LAST_VALUE){
        CHARACTER_POINTS--;
        LCK_LAST_VALUE = x;
        ui->points_label->setNum(CHARACTER_POINTS);
    }
    else if(x < LCK_LAST_VALUE)
    {
        CHARACTER_POINTS++;
        ui->points_label->setNum(CHARACTER_POINTS);
        LCK_LAST_VALUE = x;
    }

    if(CHARACTER_POINTS < 0)
        ui->points_label->setStyleSheet("color:red;");
    else
        ui->points_label->setStyleSheet("color:white;");
}

void MainMenu::update_progress()
{
    if()
}

void MainMenu::on_finish_button_clicked()
{

}

void MainMenu::on_name_edit_editingFinished()
{
    if(ui->name_edit->text() == NULL)
        name_set = 0;
    else{
        name_set = 1;

    }

}
