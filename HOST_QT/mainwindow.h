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

private:
    Ui::MainWindow *ui;
    int hid_open();
};

#endif // MAINWINDOW_H
