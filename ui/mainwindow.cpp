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

    bool dbConnected = DbConnection::getInstance().connect();

    qDebug() << dbConnected;

    this->setCentralWidget(&racerView);

    this->loginWindow.prompt();

//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
//    db.setDatabaseName("DRIVER={SQL SERVER};SERVER=DESKTOP-B6KDFI4\\SQLEXPRESS;DATABASE=wzemlik;");
//    //db.setUserName("DESKTOP-B6KDFI4\\Tojwek");
////    db.setPassword("");
//    bool ok = db.open();
//    qDebug() << ok;

//    if (ok)
//    {
//        QSqlQuery query(db);
//        query.prepare("SELECT * FROM Laps");
//        qDebug() << query.exec() << query.lastError();

//        while (query.next())
//        {
//            qDebug() << query.value(0).toInt()
//                     << query.value(1).toInt()
//                     << query.value(2).toInt()
//                     << query.value(3).toString();
//        }
//    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPushButton(bool)
{
   loginWindow.prompt();
}


void MainWindow::onLoginEntered(int userType, QString name, QString password)
{

}

void MainWindow::onLoginCancelled()
{
    qDebug() << "Cancelled";
}
