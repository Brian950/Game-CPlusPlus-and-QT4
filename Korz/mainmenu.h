#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>

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

    void on_pushButton_3_clicked();

    void strength_value(int);

    void speed_value(int);

    void guns_value(int);

    void luck_value(int);


private:
    Ui::MainMenu *ui;
};

#endif // MAINMENU_H
