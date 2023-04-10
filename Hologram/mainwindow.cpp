#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include "buttonhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ButtonHandler button = ButtonHandler();
    button.handleButtonPress();
    /*
    QVideoWidget *videoWidget = new QVideoWidget(this);
    setCentralWidget(videoWidget);
    QMediaPlayer *mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(videoWidget);
    */
}



MainWindow::~MainWindow()
{
    delete ui;
}

