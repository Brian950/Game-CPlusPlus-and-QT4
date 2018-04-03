#ifndef STORYTHREAD_H
#define STORYTHREAD_H

#include <QThread>
#include <QString>
#include <QFile>
#include <QTextStream>

class StoryThread : public QThread
{
    Q_OBJECT
public:
    explicit StoryThread(QObject *parent = 0);
    void run();
    bool part_1_complete;
    bool part_2_complete;
    bool part_3_complete;
    bool part_4_complete;
    bool part_5_complete;
    bool part_6_complete;
    bool part_7_complete;
private:
    int tut_text_position;
    QStringList tut_text_ptr;
    void load_file(QStringList &tut_text_ptr);
    void tutorial_part_1(QStringList &tut_text_ptr);
    void tutorial_part_2(QStringList &tut_text_ptr);
    void tutorial_part_3(QStringList &tut_text_ptr);
    void tutorial_part_4(QStringList &tut_text_ptr);
    void room_1_part_1(QStringList &tut_text_ptr);
    void room_2_part_1(QStringList &tut_text_ptr);
    void room_2_part_2(QStringList &tut_text_ptr);
signals:
    void update_story(QString);
    void spawn_tutorial_rects();
    void spawn_tutorial_enemy();
    void start_fight();

public slots:

};

#endif // STORYTHREAD_H
