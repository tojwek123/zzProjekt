#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    LoginWindow loginWindow;

private:
    Ui::MainWindow *ui;

private slots:
    void onPushButton(bool);
    void onLoginEntered(AppUserType type, QString name, QString password);
    void onLoginCancelled();
};

#endif // MAINWINDOW_H
