#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "backend/appuser.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    void prompt();

private:
    Ui::LoginWindow *ui;

private slots:
    void onOkButtonClicked(bool);
    void onCancelButtonClicked(bool);

signals:
    void loginEntered(AppUserType type, QString login, QString password);
    void loginCancelled();
};

#endif // LOGINWINDOW_H
