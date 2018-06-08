#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pCentralWidget(new QWidget()),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&loginWindow, &LoginWindow::loginEntered,
            this, &MainWindow::onLoginEntered);
    connect(&loginWindow, &LoginWindow::loginCancelled,
            this, &MainWindow::onLoginCancelled);

    bool dbConnected = DbConnection::getInstance().connect();

    ui->statusBar->addWidget(&this->statusBarLabel);

    this->createMenus();

    /* Initially user is logged out so display this view */
    onLogOutActionTriggered(false);

    onLoginEntered(2, 1, "Bolo");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus()
{
    pProfileMenu = new QMenu("&Profile", ui->menuBar);

    pSwitchUserAction = new QAction("&Switch User", pProfileMenu);
    pLogOutAction = new QAction("&Log Out", pProfileMenu);
    pProfileSettings = new QAction("&Profile Settings", pProfileMenu);

    pProfileMenu->addAction(pSwitchUserAction);
    pProfileMenu->addAction(pLogOutAction);
    pProfileMenu->addAction(pProfileSettings);
    ui->menuBar->addMenu(pProfileMenu);

    pLogOutAction->setVisible(false);
    pProfileSettings->setVisible(false);

    connect(pSwitchUserAction, &QAction::triggered,
            this, &MainWindow::onSwitchUserActionTriggered);

    connect(pLogOutAction, &QAction::triggered,
            this, &MainWindow::onLogOutActionTriggered);

    connect(pProfileSettings, &QAction::triggered,
            this, &MainWindow::onProfileSettingsTriggered);
}

void MainWindow::onLoginEntered(int userType, int userId, QString userName)
{
    auto pOldCentralWidget = pCentralWidget;
    this->currentUserId = userId;
    this->currentUserName = userName;

    switch (userType)
    {
    case LoginWindow::UserTypeRacer:
        pCentralWidget = new RacerView(userId, userName);
        break;
    case LoginWindow::UserTypeAdmin:
        pCentralWidget = new AdminView();
        break;
    default:
        onLogOutActionTriggered(false);
        return;
        break;
    }

    this->setCentralWidget(pCentralWidget);

    this->statusBarLabel.setText("Logged in as: " + userName + " (" + LoginWindow::userTypeToStr(userType) + ")");

    delete pOldCentralWidget;

    pLogOutAction->setVisible(true);
    pProfileSettings->setVisible(true);
    pSwitchUserAction->setText("&Switch User");
}

void MainWindow::onLoginCancelled()
{
    qDebug() << "Cancelled";
}

void MainWindow::onSwitchUserActionTriggered(bool)
{
    this->loginWindow.prompt();
}

void MainWindow::onLogOutActionTriggered(bool)
{
    auto pOldCentralWidget = pCentralWidget;
    this->pCentralWidget = new QWidget();
    this->setCentralWidget(this->pCentralWidget);
    delete pOldCentralWidget;
    this->statusBarLabel.setText("Logged out");

    pLogOutAction->setVisible(false);
    pProfileSettings->setVisible(false);
    pSwitchUserAction->setText("&Log In");
}

void MainWindow::onProfileSettingsTriggered(bool)
{
    profileSettings.showProfile(this->currentUserId);
}
