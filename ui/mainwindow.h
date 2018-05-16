#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCryptographicHash>
#include "loginwindow.h"
#include "racerview.h"
#include "backend/dbconnection.h"

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
    RacerView racerView;

private:
    Ui::MainWindow *ui;

private slots:
    void onPushButton(bool);
    void onLoginEntered(int userType, QString name, QString password);
    void onLoginCancelled();
};

#endif // MAINWINDOW_H
