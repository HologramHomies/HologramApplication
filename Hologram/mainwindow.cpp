#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QThread>
#include <QFileDialog>
#include <QVideoWidget>
#include <QVBoxLayout>
#include "buttonhandler.h"

void MainWindow::onButtonPressed(int buttonId)
{
    // Update the text box with the button ID
    //ui->textEdit->setText(QString::number(buttonId));

        // Define the path to the directory containing the video files
        QString videoDirPath = "/home/kiet/Videos";

        // Load the video file corresponding to the button ID
        QString videoFileName;
        switch (buttonId) {
            case 1:
                videoFileName = "1.mp4";
                break;
            case 2:
                videoFileName = "2.mp4";
                break;
            case 3:
                videoFileName = "3.mp4";
                break;
            case 4:
                videoFileName = "4.mp4";
            break;
            case 5:
                videoFileName = "5.mp4";
            break;
            case 6:
                videoFileName = "6.mp4";
            break;
            case 7:
                videoFileName = "7.mp4";
            break;
            case 8:
                videoFileName = "8.mp4";
            break;
            // Add more cases for additional videos
            default:
                // Handle unexpected button IDs
                return;
        }

        QString videoPath = videoDirPath + "/" + videoFileName;

        // Load the video file into the media player and start playback
          player->setMedia(QUrl::fromLocalFile(videoPath));
          player->play();


}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonThread = new QThread();
    button_handler = new ButtonHandler();
    button_handler->moveToThread(buttonThread);
    button_handler->moveToThread(buttonThread);
    connect(buttonThread, &QThread::started, button_handler, &ButtonHandler::listenToButtons);

    // Connect the buttonPressed signal to the onButtonPressed slot
    connect(button_handler, &ButtonHandler::buttonPressed,
            this, &MainWindow::onButtonPressed);

    buttonThread->start();

       player = new QMediaPlayer;
       videoWidget = new QVideoWidget;
       videoWidget->setBrightness(-50);
       videoWidget->setContrast(-50);
       player->setPosition(10000);
       connect(player,&QMediaPlayer::positionChanged,[=](int value){

           if(value>=15000){
               player->stop();
           }

       });
       player->setVideoOutput(videoWidget);

       // Create a push button to open a file
       QPushButton* pushButton = new QPushButton(tr("Open File"), this);
       connect(pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

       // Create a layout and add the widgets to it
       QVBoxLayout* layout = new QVBoxLayout;
       layout->addWidget(videoWidget);
       layout->addWidget(pushButton);

       // Set the layout as the central widget of the main window
       QWidget* centralWidget = new QWidget(this);
       centralWidget->setLayout(layout);
       setCentralWidget(centralWidget);


    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));

}

MainWindow::~MainWindow()
{
    buttonThread->quit();
    //buttonThread->wait();
    delete button_handler;
    delete buttonThread;
    delete ui;
}




void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                       "/home/kiet/Videos",
                                                       tr("Text files (*.txt);;XML files (*.xml);;Video files (*.mp4 *.avi *.mkv *.mov);;All files (*.*)"));
       if (!fileName.isEmpty()) {
           // Set the media player's source to the selected file
           player->setMedia(QUrl::fromLocalFile(fileName));
           player->play();
       }

}

