#ifndef PLANRACEDIALOG_H
#define PLANRACEDIALOG_H

#include <QDialog>
#include <QDate>
#include <QRadioButton>
#include <QListWidgetItem>
#include <QMessageBox>
#include <backend/dbconnection.h>

namespace Ui {
class PlanRaceDialog;
}

class PlanRaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlanRaceDialog(QWidget *parent = 0);
    ~PlanRaceDialog();
    void plan(const int userId);

private:
    static const char TimeFormat[];

    Ui::PlanRaceDialog *ui;
    int userId;
    QVector<int> availableDateIds;
    QVector<QDateTime> availableDates;

signals:
    void raceReserved();

private slots:
    void onCalendarClicked(const QDate &date);
    void onTimeListItemClicked(QListWidgetItem *pItem);
    void onCarListItemDoubleClicked(QListWidgetItem*);
    void onOkButtonClicked(bool);
    void onCancelButtonClicked(bool);
};

#endif // PLANRACEDIALOG_H
