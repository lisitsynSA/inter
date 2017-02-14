#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hid_code.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //closeEvent(QCloseEvent *event);

private slots:
    void start_hid();
    void stop_hid();
    void file_load();
    void send_target();
    void recv_target();
    void ping();

private:
    Ui::MainWindow *ui;
    int hid_open();
    void enableSendInterface(bool enable);
    void Send(enum MSG_CODE code, char size = 0, const char* msg = NULL);
};

#endif // MAINWINDOW_H
