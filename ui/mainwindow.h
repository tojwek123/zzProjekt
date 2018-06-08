#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QCryptographicHash>
#include "loginwindow.h"
#include "profilesettings.h"
#include "racerview.h"
#include "adminview.h"
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
    ProfileSettings profileSettings;
    QWidget *pCentralWidget;

private:
    Ui::MainWindow *ui;

    QMenu *pProfileMenu;
    QAction *pSwitchUserAction;
    QAction *pLogOutAction;
    QAction *pProfileSettings;
    QLabel statusBarLabel;

    QString currentUserName;
    int currentUserId;

    void createMenus();

private slots:
    void onLoginEntered(int userType, int userId, QString userName);
    void onLoginCancelled();

    void onSwitchUserActionTriggered(bool);
    void onLogOutActionTriggered(bool);
    void onProfileSettingsTriggered(bool);
};

#endif // MAINWINDOW_H
