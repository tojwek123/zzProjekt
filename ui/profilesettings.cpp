#include "profilesettings.h"
#include "ui_profilesettings.h"

ProfileSettings::ProfileSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileSettings)
{
    ui->setupUi(this);

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setModal(true);

    connect(ui->saveButton, &QPushButton::clicked,
            this, &ProfileSettings::onSaveButtonClicked);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &ProfileSettings::onCancelButtonClicked);

    ui->userNameLineEdit->setEnabled(false);
}

ProfileSettings::~ProfileSettings()
{
    delete ui;
}

void ProfileSettings::showProfile(const int userId)
{
//    auto dbConnection = DbConnection::getInstance();
    this->userId = userId;

    QString userName;
    QString firstName;
    QString secondName;

    DbConnection::getInstance().fetchUserDetails(userId, userName, firstName, secondName);

    ui->userNameLineEdit->setText(userName);
    ui->firstNameLineEdit->setText(firstName);
    ui->secondNameLineEdit->setText(secondName);

    ui->oldPasswordLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    ui->repeatPasswordLineEdit->clear();

    this->show();
}

void ProfileSettings::onSaveButtonClicked(bool)
{
    bool ok = true;

    if (!ui->oldPasswordLineEdit->text().isEmpty())
    {
        ok = DbConnection::getInstance().validateLogin(ui->userNameLineEdit->text(), ui->oldPasswordLineEdit->text());

        if (ok)
        {
            if (ui->newPasswordLineEdit->text() != ui->repeatPasswordLineEdit->text())
            {
                QMessageBox::warning(this, "Warning", "Repeated password must be the same as new password.");
                ok = false;
            }
            else
            {
                if (!ui->newPasswordLineEdit->text().isEmpty())
                {
                    /* Validate password */
                    if (ui->newPasswordLineEdit->text().length() < MinPasswordLength)
                    {
                        QMessageBox::warning(this, "Warning", QString("Password must have at least %1 characters.").arg(MinPasswordLength));
                        ok = false;
                    }
                    else
                    {
                        /* Save new password only if it's not empty */
                        ok = DbConnection::getInstance().changePassword(this->userId, ui->newPasswordLineEdit->text());

                        if (!ok)
                        {
                            QMessageBox::critical(this, "Error", "An error occurred during database connection.");
                        }
                    }
                }
            }
        }
        else
        {
            QMessageBox::warning(this, "Warning", QString("Incorrect old password."));
        }
    }

    if (ok)
    {
        ok = DbConnection::getInstance().updateUserDetails(this->userId, ui->firstNameLineEdit->text(), ui->secondNameLineEdit->text());

        if (!ok)
        {
            QMessageBox::critical(this, "Error", "An error occurred during database connection.");
        }
    }

    if (ok)
    {
        this->hide();
    }
}

void ProfileSettings::onCancelButtonClicked(bool)
{
    this->hide();
}
