#ifndef REFEREEVIEW_H
#define REFEREEVIEW_H

#include <QWidget>
#include <QTimeEdit>
#include <QMessageBox>
#include "backend/dbconnection.h"
#include "backend/datetimetablewidgetitem.h"

namespace Ui {
class AdminView;
}

class AdminView : public QWidget
{
    Q_OBJECT

public:
    explicit AdminView(QWidget *parent = 0);
    ~AdminView();

private:
    Ui::AdminView *ui;

    void updateRaceTable();

private slots:
    void onRacesTableItemClicked(QTableWidgetItem*);
    void onRacesTableCellChanged(int row, int col);
    void onCloseRaceButtonClicked(bool);
};

#endif // REFEREEVIEW_H
