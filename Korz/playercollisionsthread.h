#ifndef PLAYERCOLLISIONSTHREAD_H
#define PLAYERCOLLISIONSTHREAD_H
#include <QThread>

class PlayerCollisionsThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayerCollisionsThread(QObject *parent = 0);
    void run();
private:

signals:

public slots:

};


#endif // PLAYERCOLLISIONSTHREAD_H
