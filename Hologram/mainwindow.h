#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QString>
#include "buttonhandler.h"
#include "video_config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    video_config** video_list = new video_config*[8];
    QString folder_path;
    int num_videos;

private slots:
    void onButtonPressed(int buttonId);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ButtonHandler *button_handler;
    QThread *buttonThread;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
};
#endif // MAINWINDOW_H
