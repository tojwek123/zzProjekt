#ifndef PROFILESETTINGS_H
#define PROFILESETTINGS_H

#include <QDialog>
#include <QMessageBox>
#include "backend/dbconnection.h"

namespace Ui {
class ProfileSettings;
}

class ProfileSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileSettings(QWidget *parent = 0);
    ~ProfileSettings();

    void showProfile(const int userId);

private:
    Ui::ProfileSettings *ui;
    int userId;

    static const int MinPasswordLength = 5;

private slots:
    void onSaveButtonClicked(bool);
    void onCancelButtonClicked(bool);
};

#endif // PROFILESETTINGS_H
