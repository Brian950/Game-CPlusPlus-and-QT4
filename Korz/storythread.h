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
private:
    int tut_text_position;
    QStringList tut_text_ptr;
    void load_file(QStringList &tut_text_ptr);
    void tutorial_part_1(QStringList &tut_text_ptr);
    void tutorial_part_2(QStringList &tut_text_ptr);
    void tutorial_part_3(QStringList &tut_text_ptr);
signals:
    void update_story(QString);
    void spawn_tutorial_rects();
    void spawn_tutorial_enemy();

public slots:

};

#endif // STORYTHREAD_H
