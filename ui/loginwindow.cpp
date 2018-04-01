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

    connect(ui->okButton, &QPushButton::clicked,
            this, &LoginWindow::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &LoginWindow::onCancelButtonClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
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
        this->hide();
        AppUserType type = static_cast<AppUserType>(this->ui->userTypeComboBox->currentIndex());
        QString name = this->ui->loginLineEdit->text();
        QString password = this->ui->passwordLineEdit->text();
        emit this->loginEntered(type, name, password);
    }
}

void LoginWindow::onCancelButtonClicked(bool)
{
    this->hide();
    emit this->loginCancelled();
}
