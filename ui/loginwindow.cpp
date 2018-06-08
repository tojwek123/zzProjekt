#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setFixedSize(this->size());
    this->setModal(true);

    this->ui->userTypeComboBox->addItem(userTypeToStr(UserTypeRacer), UserTypeRacer);
    this->ui->userTypeComboBox->addItem(userTypeToStr(UserTypeAdmin), UserTypeAdmin);

    connect(ui->okButton, &QPushButton::clicked,
            this, &LoginWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &LoginWindow::onCancelButtonClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

QString LoginWindow::userTypeToStr(int type)
{
    switch (type)
    {
    case LoginWindow::UserTypeRacer:
        return "Racer";
    case LoginWindow::UserTypeAdmin:
        return "Administrator";
    }

    return "";
}

void LoginWindow::prompt()
{
    this->ui->userTypeComboBox->setFocus();
    this->ui->loginLineEdit->clear();
    this->ui->passwordLineEdit->clear();
    this->show();
}

void LoginWindow::onOkButtonClicked(bool)
{
    if (this->ui->loginLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Login field cannot be empty.");
    }
    else if (this->ui->passwordLineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Password field cannot be empty.");
    }
    else
    {
        int selectedUserType = this->ui->userTypeComboBox->currentData().toInt();
        QString userName = this->ui->loginLineEdit->text();
        QString password = this->ui->passwordLineEdit->text();
        int userType;

        DbConnection::getInstance().fetchUserType(userName, userType);

        bool loginValid = DbConnection::getInstance().validateLogin(userName, password) & (userType == selectedUserType);

        if (loginValid)
        {
            int userId = -1;
            DbConnection::getInstance().fetchUserId(userName, userId);

            this->hide();
            emit this->loginEntered(userType, userId, userName);
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Incorrect password");
        }
    }
}

void LoginWindow::onCancelButtonClicked(bool)
{
    this->hide();
    emit this->loginCancelled();
}
