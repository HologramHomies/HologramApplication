#include "mainwindow.h"

#include <QApplication>
#include <QMediaplayer>
#include <QVideoWidget>

// Pulled from configurationApp
class videoSettings{
public:
    int brightnessValue;
    int constrastValue;
    double fromTrim;
    double toTrim;
    QString path;
    QMediaPlayer *player;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
