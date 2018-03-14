#include "storythread.h"
#include "QDebug"

StoryThread::StoryThread(QObject *parent) : QThread(parent)
{
    tut_text_position = 0;
    part_1_complete = false;
    part_2_complete = false;
}

void StoryThread::run()
{
    if(part_1_complete == false){
        load_file(tut_text_ptr);
        tutorial_part_1(tut_text_ptr);
    }
    else if(part_2_complete == false){
        tutorial_part_2(tut_text_ptr);
    }
}

void StoryThread::load_file(QStringList &tut_text_ptr){
    QFile inputFile("/home/brian/Korz/trunk/Korz/tutorial_story.txt");
    QString line;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          line = in.readLine();
          tut_text_ptr << line;
       }
       inputFile.close();
    }
}

void StoryThread::tutorial_part_1(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = 0; x < 3; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        tut_text_position++;
        sleep(1);
    }
    emit spawn_tutorial_rects();
    part_1_complete = true;
}

void StoryThread::tutorial_part_2(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = tut_text_position; x < 3; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(3);
        tut_text_position = x;
    }
    part_2_complete = true;
}

