#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tryButton, SIGNAL(pressed()), this, SLOT(start_hid()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_hid()
{
    qDebug() << "START HID CONNECTION";

    if(hid_open()>0){
        qDebug() << "HID device is opened (VID=0x483, PID=0x5711)";
        ui->statusLabel->setText(QString("Status: Connect"));
    }else{
        qDebug() << "HID device is not opened";
        ui->statusLabel->setText(QString("Status: Disconnect"));
        return;
    }
    return;
}
