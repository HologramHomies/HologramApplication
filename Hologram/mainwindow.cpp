#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMediaPlayer>
#include <QThread>
#include "buttonhandler.h"

void MainWindow::onButtonPressed(int buttonId)
{
    // Update the text box with the button ID
    ui->textEdit->setText(QString::number(buttonId));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread* buttonThread = new QThread();
    ButtonHandler* button_handler = new ButtonHandler();
    button_handler->moveToThread(buttonThread);
    button_handler->moveToThread(buttonThread);
    connect(buttonThread, &QThread::started, button_handler, &ButtonHandler::listenToButtons);

    // Connect the buttonPressed signal to the onButtonPressed slot
    connect(button_handler, &ButtonHandler::buttonPressed,
            this, &MainWindow::onButtonPressed);

    buttonThread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}



