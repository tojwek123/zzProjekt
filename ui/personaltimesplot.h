#ifndef PERSONALTIMESPLOT_H
#define PERSONALTIMESPLOT_H

#include <QDialog>

namespace Ui {
class PersonalTimesPlot;
}

class PersonalTimesPlot : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalTimesPlot(QWidget *parent = 0);
    ~PersonalTimesPlot();

    void plotTimes(const QMap<QDateTime, QTime> &times);

private:
    Ui::PersonalTimesPlot *ui;
};

#endif // PERSONALTIMESPLOT_H
