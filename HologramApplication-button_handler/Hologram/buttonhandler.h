#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QObject>
#include <QPushButton>



class ButtonHandler
{

public slots:
    ButtonHandler();
    void handleButtonPress();
    void playVideo();
private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QPushButton* button1;
};


#endif // BUTTONHANDLER_H
