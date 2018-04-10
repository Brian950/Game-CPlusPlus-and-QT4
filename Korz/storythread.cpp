#include "storythread.h"
#include "QDebug"

StoryThread::StoryThread(QObject *parent) : QThread(parent)
{
    tut_text_position = 0;
    part_1_complete = false;
    part_2_complete = false;
    part_3_complete = false;
    part_4_complete = false;
    part_5_complete = false;
    part_6_complete = false;
    part_7_complete = false;
    part_8_complete = false;
    part_9_complete = false;
    part_10_complete = false;
    part_11_complete = false;
    part_12_complete = false;
    part_13_complete = false;
    part_14_complete = false;
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
    else if(part_3_complete == false){
        tutorial_part_3(tut_text_ptr);
    }
    else if(part_4_complete == false){
        tutorial_part_4(tut_text_ptr);
    }
    else if(part_5_complete == false){
        room_1_part_1(tut_text_ptr);
    }
    else if(part_6_complete == false){
        room_2_part_1(tut_text_ptr);
    }
    else if(part_7_complete == false){
        room_2_part_2(tut_text_ptr);
    }
    else if(part_8_complete == false){
        room_3_part_1(tut_text_ptr);
    }
    else if(part_9_complete == false){
        room_3_part_2(tut_text_ptr);
    }
    else if(part_10_complete == false){
        room_2_part_3(tut_text_ptr);
    }
    else if(part_11_complete == false){
        room_4_part_1(tut_text_ptr);
    }
    else if(part_12_complete == false){
        room_4_part_2(tut_text_ptr);
    }
    else if(part_13_complete == false){
        room_2_part_4(tut_text_ptr);
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
    for(int x = tut_text_position; x < 5; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        if(x != 5-1)
            sleep(1);
        tut_text_position = x;
    }
    part_2_complete = true;
}

void StoryThread::tutorial_part_3(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = tut_text_position; x < 8; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    emit spawn_tutorial_enemy();
    part_3_complete = true;
}

void StoryThread::tutorial_part_4(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = tut_text_position; x < 10; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_4_complete = true;
}

void StoryThread::room_1_part_1(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = tut_text_position; x < 12; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_5_complete = true;
}

void StoryThread::room_2_part_1(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 15; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    emit start_fight();
    part_6_complete = true;
}

void StoryThread::room_2_part_2(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 18; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_7_complete = true;
}

void StoryThread::room_3_part_1(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 19; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    emit spawn_room_3_enemies();
    part_8_complete = true;
}

void StoryThread::room_3_part_2(QStringList &tut_text_ptr)
{
    QString line;
    for(int x = tut_text_position; x < 20; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_9_complete = true;
}

void StoryThread::room_2_part_3(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 21; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_10_complete = true;
}

void StoryThread::room_4_part_1(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 22; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_11_complete = true;
}

void StoryThread::room_4_part_2(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 23; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_12_complete = true;
}

void StoryThread::room_2_part_4(QStringList &tut_text_ptr){
    QString line;
    for(int x = tut_text_position; x < 24; x++){
        line = tut_text_ptr.at(x);
        emit update_story(line);
        sleep(1);
        tut_text_position = x;
    }
    part_13_complete = true;
}
