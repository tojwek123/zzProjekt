#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &MainWindow::onPushButton);
    connect(&loginWindow, &LoginWindow::loginEntered,
            this, &MainWindow::onLoginEntered);
    connect(&loginWindow, &LoginWindow::loginCancelled,
            this, &MainWindow::onLoginCancelled);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButton(bool)
{
   loginWindow.prompt();
}


void MainWindow::onLoginEntered(AppUserType type, QString name, QString password)
{
    qDebug() << static_cast<int>(type) << name << password;
}

void MainWindow::onLoginCancelled()
{
    qDebug() << "Cancelled";
}
