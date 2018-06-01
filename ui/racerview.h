#ifndef RACERVIEW_H
#define RACERVIEW_H

#include <QWidget>
#include <QMenu>
#include "backend/dbconnection.h"
#include "backend/timetablewidgetitem.h"
#include "backend/datetimetablewidgetitem.h"
#include "backend/qcustomplot/qcustomplot.h"
#include "ui/planracedialog.h"
#include "ui/personaltimesplot.h"

namespace Ui {
class RacerView;
}

class RacerView : public QWidget
{
    Q_OBJECT

public:
    explicit RacerView(QWidget *parent = 0);
    ~RacerView();

    void setRacer(const int userId, const QString &userName);

private:
    static const QColor leaderboardUserRow;

    Ui::RacerView *ui;
    QString userName;
    int userId;
    PlanRaceDialog planRaceDialog;
    PersonalTimesPlot personalTimesPlot;

    void updateReservedLaps();
    void updatePersonalLapTimes();
    void updateLeaderboard();

private slots:
    void onMainTabCurrentChanged(int index);
    void onFindMyBestTimeClicked(bool);
    void onPlanNextRaceButtonClicked(bool);
    void onPlanRaceDialogRaceReserved();
    void onReservedRacesTableCustomContextMenuRequested(const QPoint &pt);
    void onCancelReservation();
    void onPlotPersonalTimesButtonClicked(bool);
};

#endif // RACERVIEW_H
