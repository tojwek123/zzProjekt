#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "backend/dbconnection.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

    static const int UserTypeRacer = 1;
    static const int UserTypeAdmin = 2;

    static QString userTypeToStr(int type);

    void prompt();

private:
    Ui::LoginWindow *ui;

private slots:
    void onOkButtonClicked(bool);
    void onCancelButtonClicked(bool);

signals:
    void loginEntered(int userType, int userId, QString userName);
    void loginCancelled();
};

#endif // LOGINWINDOW_H
