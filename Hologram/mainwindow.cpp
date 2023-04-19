#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QThread>
#include <QFileDialog>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QFile>
#include "buttonhandler.h"
#include "video_config.h"

void MainWindow::onButtonPressed(int buttonId)
{
    // Update the text box with the button ID
    //ui->textEdit->setText(QString::number(buttonId));

    // Define the path to the directory containing the video files
    QString videoDirPath = "/home/kiet/Videos";

    // Load the video file corresponding to the button ID
    QString videoFileName;
    int button_id = 0;
    switch (buttonId) {
        case 1:
            button_id = 0;
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

    // Load the video file into the media player and start playback
    videoWidget->setBrightness(video_list[button_id]->getBrightness());
    videoWidget->setContrast(video_list[button_id]->getContrast());
    player->setPosition(video_list[button_id]->getStart_pos());
    player->setMedia(QUrl::fromLocalFile(video_list[button_id]->getVideo_path()));
    connect(player,&QMediaPlayer::positionChanged,[=](int value){

        if(value>= video_list[button_id]->getEnd_pos()){
            player->stop();
        }

    });
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
    // Find xml file
    QString xml_file_path = "";

    while(xml_file_path == ""){
        // Get config folder
        QString config_folder = QFileDialog::getOpenFileName(this,
            tr("Open config usb"), "/home/");

        // Search directory for xml file
        QStringList nameFilter("*.xml");
        QDir directory(config_folder);
        QStringList xml_file_ext = directory.entryList(nameFilter);

        // Check xml file exists and set to file path
        if(xml_file_ext[0] != NULL){
            QString xml_file_path = config_folder + xml_file_ext[0];
        }
    }

    // Open xml file
    // Load xml file as raw data
    QFile f(xml_file_path);
    if (!f.open(QIODevice::ReadOnly ))
    {
        xml_file_path ="";
        while(xml_file_path == ""){
            // Get config folder
            QString config_folder = QFileDialog::getOpenFileName(this,
                tr("Open config usb"), "/home/");

            // Search directory for xml file
            QStringList nameFilter("*.xml");
            QDir directory(config_folder);
            QStringList xml_file_ext = directory.entryList(nameFilter);

            // Check xml file exists and set to file path
            if(xml_file_ext[0] != NULL){
                QString xml_file_path = config_folder + xml_file_ext[0];
            }
        }
    }
    // Set data into the QDomDocument before processing
    QXmlStreamReader reader(&f);
    f.close();


    if (reader.readNextStartElement()) {
        if (reader.name() == "configuration"){
            int num_videos = 0;
            while(reader.readNext()){
                if(reader.name() == "button"){
                    int buttonID = reader.attributes().value("id").toInt();
                    QString video_path = reader.attributes().value("video_path").toString();
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
                    reader.skipCurrentElement();
                }
            }
        }
        else{
            reader.raiseError(QObject::tr("Incorrect file"));
        }
    }
}

