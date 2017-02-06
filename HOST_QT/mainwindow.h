#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void file_load();
    void send_target();
    void recv_target();

private:
    Ui::MainWindow *ui;
    int hid_open();
    void enableSendInterface(bool enable);
};

#endif // MAINWINDOW_H
