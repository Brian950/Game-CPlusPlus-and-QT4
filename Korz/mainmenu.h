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
#include <QStyle>
#include <storythread.h>
#include <QDesktopWidget>
#include "container.h"
#include "playercollisionsthread.h"
#include "weapon.h"
#include "medkit.h"
#include "enemy.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();
//Function prototype examples:
public slots:
    void update_story(QString story_text);
    void spawn_tutorial_rects();
    void tutorial_part_2();
    void rectangle_destroyed();
    void open_inventory(QString, Container*);
    void spawn_tutorial_enemy();
protected:
    void mousePressEvent(QMouseEvent *event);
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
    void tutorial_part_1();
    void tutorial_part_3();
    void tutorial_part_4();
    void on_pushButton_3_clicked();
    void on_north_button_clicked();
    void on_south_button_clicked();
    void on_east_button_clicked();
    void on_west_button_clicked();
    void on_inventory_back_button_clicked();
    void on_add_to_inventory_button_clicked();
    void on_remove_from_inventory_button_clicked();
    void on_inventory_button_clicked();
    void on_main_inventory_back_clicked();
    void on_use_item_button_clicked();
    void update_health_bar();
    void on_tutorial_enemy_dead();
    void spawn_enemy(int, QPoint);

private:
    Ui::MainMenu *ui;
    DB_Controller *dbc;
    Character *player = NULL;
    StoryThread *story_thread;
    QGraphicsScene *tutorial_scene;
    QSet<int> pressedKeys; //Holds all currently held down keys
    Container *active_container;

    int CHARACTER_POINTS = 20;
    int STR_LAST_VALUE = 0, SPD_LAST_VALUE = 0, GUN_LAST_VALUE = 0, LCK_LAST_VALUE = 0;
    int name_set = 0;
    int special_set = 0;
    QString CHARACTER_NAME = "";

    CustomRect *rect1;
    CustomRect *rect2;
    CustomRect *rect3;
    CustomRect *rect4;
    int tut_rect_counter = 0;
    bool tut_cont_first_time = true;
    QList<Enemy*> *active_enemy_list;
};

#endif // MAINMENU_H
