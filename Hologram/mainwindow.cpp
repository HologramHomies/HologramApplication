#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVideoWidget>
#include <QMediaPlayer>
#include "button.h"
#include <QDebug>

#TODO CHANGE BACKGROUND COLOR


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Connect to UI
    ui->setupUi(this);

   QGridLayout * existingLayout = dynamic_cast < QGridLayout * > (ui -> grid_layout);

    // Initialize player and widget. Widget stores player in UI and Player control playback
    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *vw = new QVideoWidget;

    // Create new button
    // THIS IS FOR TESTING AND WILL BE ALTERED WHEN EXPORT IS DONE
    button button1 = button(1, "C:\\Users\\Camer\\Desktop\\sound_of_silence.mp4", 0, 0);

    // Set Label to display in window
    // From Configuration app mainwindow
//    if(dynamic_cast < QLabel * > (ui->Video_Label)){
//            vw->setSizePolicy(ui->Video_Label->sizePolicy());
//            vw->setMinimumSize(ui->Video_Label->minimumSize());
//             delete dynamic_cast < QWidget * > (ui->Video_Label);

//        //existingLayout ->removeWidget(existingLayout -> itemAtPosition(0, 0)->widget());
//    }else{
//        vw = dynamic_cast < QVideoWidget * > (ui->Video_Label);
//        //player = vw->mediaObject->service();
//    }
    if(dynamic_cast < QLabel * > (existingLayout -> itemAtPosition(0, 0)->widget())){
            vw->setSizePolicy(existingLayout -> itemAtPosition(0, 0)->widget()->sizePolicy());
            vw->setMinimumSize(existingLayout -> itemAtPosition(0,0)->widget()->minimumSize());
            delete dynamic_cast < QWidget * > (existingLayout -> itemAtPosition(0, 0)->widget());

        //existingLayout ->removeWidget(existingLayout -> itemAtPosition(0, 0)->widget());
    }else{
        vw = dynamic_cast < QVideoWidget * > (existingLayout -> itemAtPosition(0, 0)->widget());
        //player = vw->mediaObject->service();
    }

    vw->setMouseTracking(true);             // Taken from config idk what this does

    // Set player to widget
    player->setVideoOutput(vw);

    // Check that video exist
    if(button1.get_video_path() == ""){
            return;
    }

    // Set video
    player->setMedia(QUrl::fromLocalFile(button1.get_video_path()));

    // Determines size and location of video
    //vw->setGeometry(100, 100, 300, 400);
    existingLayout -> addWidget(vw, 0, 1);
    vw->show();

    player->play();

    qDebug() << player->state();
}

MainWindow::~MainWindow()
{
    delete ui;
}

