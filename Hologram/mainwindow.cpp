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

}

MainWindow::~MainWindow()
{
    delete ui;
}

