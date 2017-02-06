#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hid.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tryButton, SIGNAL(pressed()), this, SLOT(start_hid()));
    connect(ui->fileButton, SIGNAL(pressed()), this, SLOT(file_load()));
    connect(ui->sendButton, SIGNAL(pressed()), this, SLOT(send_target()));
    connect(ui->recvButton, SIGNAL(pressed()), this, SLOT(recv_target()));
    setCentralWidget(ui->gridWidget);
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
        enableSendInterface(true);
    }else{
        qDebug() << "HID device is not opened";
        enableSendInterface(false);
    }
    return;
}

void MainWindow::file_load()
{

}

int MainWindow::hid_open()
{
    return rawhid_open(1, 0x483, 0x5711, -1, -1);
}


#define wait_timeout 300 //300
unsigned char TransmitBuffer[65];
unsigned char ReceiveBuffer[65];

void MainWindow::send_target()
{
    TransmitBuffer[0] = 1; //HID command send

    //strcpy((char *)TransmitBuffer+1,"Hello World");

    //scanf("%s", TransmitBuffer+1);
    strcpy((char *)TransmitBuffer+1, ui->sendLineEdit->text().toStdString().data());
    //Всегда передаем 65 байт
    if(rawhid_send(0, TransmitBuffer, 65, wait_timeout)==-1){
        enableSendInterface(false);
        qDebug() << "HID device error";
        return;
    }

    qDebug() << "SEND : " << (char*)(TransmitBuffer + 1);
}

void MainWindow::recv_target()
{
    //Всегда принимаем 65 байт
    int ReceiveLength = rawhid_recv(0, ReceiveBuffer, 65, wait_timeout);
    if (ReceiveLength==-1){
        qDebug() << "HID device error";
        enableSendInterface(false);
        return;
    }

    qDebug() << "RECV (" << ReceiveLength << "): " << (char*)ReceiveBuffer;
    ui->recvLineEdit->setText(QString((char*)ReceiveBuffer));
    ui->recvNumber->display(ReceiveLength);

    if (ReceiveLength == 0)
    {
        ui->recvLineEdit->setText(QString(""));
    }
}


void MainWindow::enableSendInterface(bool enable)
{
    ui->sendButton->setEnabled(enable);
    ui->recvButton->setEnabled(enable);
    ui->fileButton->setEnabled(enable);

    if (enable)
        ui->statusLabel->setText(QString("Status: Connect"));
    else
        ui->statusLabel->setText(QString("Status: Disconnect"));

}
