#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "character.h"
#include "db_controller.h"
#include "customrect.h"
#include <QMessageBox>
#include <QtCore>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <textrect.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

    void on_back_button_1_clicked();

    void strength_value(int);

    void speed_value(int);

    void guns_value(int);

    void luck_value(int);

    void update_progress(int);

    void on_finish_button_clicked();

    void on_name_edit_editingFinished();

    void set_attribute_value(int, int);

    void on_reset_button_clicked();

    void on_ability_box_currentIndexChanged(int index);

    void start_tutorial(Character*);

    void on_pushButton_3_clicked();

    void on_north_button_clicked();

    void on_south_button_clicked();

    void on_east_button_clicked();

    void on_west_button_clicked();

private:
    Ui::MainMenu *ui;
    QGraphicsScene *room_scene;

    int CHARACTER_POINTS = 20;
    int STR_LAST_VALUE = 0, SPD_LAST_VALUE = 0, GUN_LAST_VALUE = 0, LCK_LAST_VALUE = 0;
    int name_set = 0;
    int special_set = 0;
    QString CHARACTER_NAME = "";
};

#endif // MAINMENU_H
