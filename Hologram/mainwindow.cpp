#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QThread>
#include <QFileDialog>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include "buttonhandler.h"
#include "video_config.h"

void MainWindow::onButtonPressed(int buttonId)
{
    // Update the text box with the button ID
    //ui->textEdit->setText(QString::number(buttonId));

    // Define the path to the directory containing the video files
    //String videoDirPath = "/home/kiet/Videos";

    // Load the video file corresponding to the button ID
    //QString videoFileName;
//    switch (buttonId) {
//        case 1:
//            button_id = 0;
//            break;
//        case 2:
//            button_id = 1;
//            break;
//        case 3:
//            button_id = 2;
//            break;
//        case 4:
//            button_id = 3;
//        break;
//        case 5:
//            button_id = 4;
//        break;
//        case 6:
//            button_id = 5;
//        break;
//        case 7:
//            button_id = 6;
//        break;
//        case 8:
//            button_id = 7;
//        break;
//        // Add more cases for additional videos
//        default:
//            // Handle unexpected button IDs
//            return;
//    }
    if(num_videos > buttonId - 1){
        qDebug() << "Playing";
        // Load the video file into the media player and start playback
        videoWidget->setBrightness(video_list[buttonId - 1]->getBrightness());
        videoWidget->setContrast(video_list[buttonId - 1]->getContrast());
        player->setPosition(video_list[buttonId - 1]->getStart_pos());
        player->setMedia(QUrl::fromLocalFile(video_list[buttonId - 1]->getVideo_path()));
        connect(player,&QMediaPlayer::positionChanged,[=](int value){

            if(value>= video_list[buttonId - 1]->getEnd_pos()){
                player->stop();
            }

        });
        player->play();
    }

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
    // Find xml file
    QString xml_file_path = "";

    while(xml_file_path == ""){
        xml_file_path = QFileDialog::getOpenFileName(this,
                                                tr("Open config usb"), "/home/");
    }
    qDebug() << xml_file_path;
    QFile f(xml_file_path);
    QFileInfo fInfo(xml_file_path);
    xml_file_path = fInfo.dir().path();

    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        xml_file_path = QFileDialog::getOpenFileName(this,
                                                tr("Open config usb"), "/home/");

        QFile f(xml_file_path);
        QFileInfo fInfo(xml_file_path);
        xml_file_path = fInfo.dir().path();
    }
    // Set data into the QDomDocument before processing
    QXmlStreamReader reader(&f);
    qDebug() << xml_file_path;
    //f.close();


    if (reader.readNextStartElement()) {
        qDebug() << xml_file_path;
        if (reader.name() == "configuration"){
            num_videos = 0;
            while(!reader.atEnd()){
                reader.readNext();
                if(reader.name() == "button" && reader.isStartElement()){
                    int buttonID = reader.attributes().value("id").toInt();
                    QString video_path = xml_file_path + "/" + QString::number(num_videos + 1) + ".mp4";
                    int brightness = reader.attributes().value("brightness").toInt();
                    int contrast = reader.attributes().value("contrast").toInt();
                    int start_pos = reader.attributes().value("start_pos").toInt();
                    int end_pos = reader.attributes().value("end_pos").toInt();

                  //Store in array
                  video_list[num_videos] = new video_config(buttonID, video_path, brightness, contrast, start_pos, end_pos);
                  // Iterate
                  num_videos++;
                }
                else{
                    qDebug() << reader.name();
                }
            }
        }
        else{
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }
    else
    {
        qDebug() << "XML Error";
    }
//    player->setMedia(QUrl::fromLocalFile(video_list[0]->getVideo_path()));
//    player->play();
    f.close();
}

