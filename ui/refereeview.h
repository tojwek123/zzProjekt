#ifndef REFEREEVIEW_H
#define REFEREEVIEW_H

#include <QWidget>
#include <QTimeEdit>
#include <QMessageBox>
#include "backend/dbconnection.h"
#include "backend/datetimetablewidgetitem.h"

namespace Ui {
class RefereeView;
}

class RefereeView : public QWidget
{
    Q_OBJECT

public:
    explicit RefereeView(QWidget *parent = 0);
    ~RefereeView();

private:
    Ui::RefereeView *ui;

    void updateRaceTable();

private slots:
    void onRacesTableItemClicked(QTableWidgetItem*);
    void onCloseRaceButtonClicked(bool);
};

#endif // REFEREEVIEW_H
