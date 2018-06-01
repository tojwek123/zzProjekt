#include "racerview.h"
#include "ui_racerview.h"

const QColor RacerView::leaderboardUserRow(240, 240, 255);

RacerView::RacerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RacerView)
{
    ui->setupUi(this);

    connect(ui->mainTab, &QTabWidget::currentChanged,
            this, &RacerView::onMainTabCurrentChanged);

    connect(ui->findMyBestTimeButton, &QPushButton::clicked,
            this, &RacerView::onFindMyBestTimeClicked);

    connect(ui->planNextRaceButton, &QPushButton::clicked,
            this, &RacerView::onPlanNextRaceButtonClicked);

    connect(&planRaceDialog, &PlanRaceDialog::raceReserved,
            this, &RacerView::onPlanRaceDialogRaceReserved);

    connect(ui->plotPersonalTimesButton, &QPushButton::clicked,
            this, &RacerView::onPlotPersonalTimesButtonClicked);

    /* Initialize reservedLapsTable */
    QStringList reservedRacesHeaderLabels;
    reservedRacesHeaderLabels.append("Date");
    reservedRacesHeaderLabels.append("Car");

    ui->reservedRacesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->reservedRacesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->reservedRacesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->reservedRacesTable->setColumnCount(reservedRacesHeaderLabels.length());
    ui->reservedRacesTable->setHorizontalHeaderLabels(reservedRacesHeaderLabels);

    ui->reservedRacesTable->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->reservedRacesTable, &QTableWidget::customContextMenuRequested,
            this, RacerView::onReservedRacesTableCustomContextMenuRequested);

    /* Initialize personalLapTimesTable */
    QStringList personalLapTimesHeaderLabels;
    personalLapTimesHeaderLabels.append("Lap Duration");
    personalLapTimesHeaderLabels.append("Date");

    ui->personalLapTimesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->personalLapTimesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->personalLapTimesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->personalLapTimesTable->setColumnCount(personalLapTimesHeaderLabels.length());
    ui->personalLapTimesTable->setHorizontalHeaderLabels(personalLapTimesHeaderLabels);

    /* Initialize leaderboardTable */
    QStringList leaderboardHeaderLabels;
    leaderboardHeaderLabels.append("Name");
    leaderboardHeaderLabels.append("Lap Duration");
    leaderboardHeaderLabels.append("Date");

    ui->leaderboardTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->leaderboardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leaderboardTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leaderboardTable->setColumnCount(leaderboardHeaderLabels.length());
    ui->leaderboardTable->setHorizontalHeaderLabels(leaderboardHeaderLabels);
}

RacerView::~RacerView()
{
    delete ui;
}

void RacerView::setRacer(const int userId, const QString &userName)
{
    this->userId = userId;
    this->userName = userName;

    onMainTabCurrentChanged(ui->mainTab->currentIndex());
}

void RacerView::updateReservedLaps()
{
    QVector<int> reservedLapIds;
    QVector<QDateTime> dates;
    QVector<QString> carBrands;
    QVector<QString> carModels;

    DbConnection::getInstance().fetchReservedLaps(this->userId, reservedLapIds, dates, carBrands, carModels);

    ui->reservedRacesTable->setSortingEnabled(false);
    ui->reservedRacesTable->setRowCount(reservedLapIds.length());

    for (int i = 0; i < reservedLapIds.length(); ++i)
    {
        DateTimeTableWidgetItem * pDateItem = new DateTimeTableWidgetItem(dates[i]);
        QTableWidgetItem * pCarItem = new QTableWidgetItem(carBrands[i] + " " + carModels[i]);

        pDateItem->setTextAlignment(Qt::AlignCenter);
        pCarItem->setTextAlignment(Qt::AlignCenter);

        /* pDateItem keeps the reservedLapId as its data */
        pDateItem->setData(Qt::UserRole, reservedLapIds[i]);

        ui->reservedRacesTable->setItem(i, 0, pDateItem);
        ui->reservedRacesTable->setItem(i, 1, pCarItem);
    }

    ui->reservedRacesTable->setSortingEnabled(true);
}

void RacerView::updatePersonalLapTimes()
{
    QVector<QTime> durations;
    QVector<QDateTime> dates;

    DbConnection::getInstance().fetchRacerLaps(this->userId, durations, dates);

    ui->personalLapTimesTable->setSortingEnabled(false);
    ui->personalLapTimesTable->setRowCount(durations.length());

    for (int i = 0; i < durations.length(); ++i)
    {
        TimeTableWidgetItem *pDurationItem = new TimeTableWidgetItem(durations[i]);
        DateTimeTableWidgetItem *pDateItem = new DateTimeTableWidgetItem(dates[i]);

        pDurationItem->setData(Qt::UserRole, durations[i]);
        pDateItem->setData(Qt::UserRole, dates[i]);

        pDurationItem->setTextAlignment(Qt::AlignCenter);
        pDateItem->setTextAlignment(Qt::AlignCenter);

        ui->personalLapTimesTable->setItem(i, 0, pDurationItem);
        ui->personalLapTimesTable->setItem(i, 1, pDateItem);
    }
    ui->personalLapTimesTable->setSortingEnabled(true);
}

void RacerView::updateLeaderboard()
{
    QVector<QString> names;
    QVector<QTime> durations;
    QVector<QDateTime> dates;

    DbConnection::getInstance().fetchLeaderboard(names, durations, dates);

    ui->leaderboardTable->setSortingEnabled(false);
    ui->leaderboardTable->setRowCount(names.length());

    for (int i = 0; i < names.length(); ++i)
    {
        QTableWidgetItem *pNameItem = new QTableWidgetItem(names[i]);
        TimeTableWidgetItem *pDurationItem = new TimeTableWidgetItem(durations[i]);
        DateTimeTableWidgetItem *pDateItem = new DateTimeTableWidgetItem(dates[i]);

        pNameItem->setTextAlignment(Qt::AlignCenter);
        pDurationItem->setTextAlignment(Qt::AlignCenter);
        pDateItem->setTextAlignment(Qt::AlignCenter);

        if (names[i] == userName)
        {
            pNameItem->setBackground(QBrush(leaderboardUserRow));
            pDurationItem->setBackground(QBrush(leaderboardUserRow));
            pDateItem->setBackground(QBrush(leaderboardUserRow));
        }

        ui->leaderboardTable->setItem(i, 0, pNameItem);
        ui->leaderboardTable->setItem(i, 1, pDurationItem);
        ui->leaderboardTable->setItem(i, 2, pDateItem);
    }

    ui->leaderboardTable->setSortingEnabled(true);
}

void RacerView::onMainTabCurrentChanged(int index)
{
    switch (index)
    {
    case 0:
        this->updateReservedLaps();
        break;
    case 1:
        this->updatePersonalLapTimes();
        break;
    case 2:
        this->updateLeaderboard();
        break;
    default:
        break;
    }
}

void RacerView::onFindMyBestTimeClicked(bool)
{
    QTableWidgetItem *pBestTimeItem = nullptr;
    int bestTimeRow = -1;

    for (int i = 0; i < ui->leaderboardTable->rowCount(); ++i)
    {
        if (this->userName == ui->leaderboardTable->item(i, 0)->text())
        {
            QTableWidgetItem *pItem = ui->leaderboardTable->item(i, 1);

            if (nullptr == pBestTimeItem)
            {
                pBestTimeItem = pItem;
                bestTimeRow = i;
            }
            else if (*pItem < *pBestTimeItem)
            {
                pBestTimeItem = pItem;
                bestTimeRow = i;
            }
        }
    }

    if (nullptr != pBestTimeItem)
    {
        ui->leaderboardTable->selectRow(bestTimeRow);
        ui->leaderboardTable->setFocus();
    }
}

void RacerView::onPlanNextRaceButtonClicked(bool)
{
    planRaceDialog.plan(this->userId);
}

void RacerView::onPlanRaceDialogRaceReserved()
{
    this->updateReservedLaps();
}

void RacerView::onReservedRacesTableCustomContextMenuRequested(const QPoint &pt)
{
    if (nullptr != ui->reservedRacesTable->itemAt(pt))
    {
        ui->reservedRacesTable->selectRow(ui->reservedRacesTable->rowAt(pt.y()));

        QMenu menu;
        QAction cancelAction("Cancel reservation");

        connect(&cancelAction, QAction::triggered,
                this, RacerView::onCancelReservation);

        menu.addAction(&cancelAction);

        menu.exec(QCursor::pos());
    }
}

void RacerView::onCancelReservation()
{
    if (QMessageBox::Yes == QMessageBox::warning(this, "Warning", "Are you sure you want to cancel reservation?", QMessageBox::Yes, QMessageBox::No))
    {
        int selectedRow = ui->reservedRacesTable->currentRow();
        int reservedRaceRow = ui->reservedRacesTable->item(selectedRow, 0)->data(Qt::UserRole).toInt();
        DbConnection::getInstance().cancelRaceReservation(reservedRaceRow);

        this->updateReservedLaps();
    }
}

void RacerView::onPlotPersonalTimesButtonClicked(bool)
{
    QMap<QDateTime, QTime> personalTimes;

    /* Get selected rows */
    QItemSelectionModel *pSelectionModel = ui->personalLapTimesTable->selectionModel();

    for (QModelIndex idx : pSelectionModel->selectedRows())
    {
        QDateTime date = ui->personalLapTimesTable->item(idx.row(), 1)->data(Qt::UserRole).toDateTime();
        QTime time = ui->personalLapTimesTable->item(idx.row(), 0)->data(Qt::UserRole).toTime();

        personalTimes.insert(date, time);
    }

    /* Display warning if 0 rows are selected */
    if (0 == personalTimes.size())
    {
        QMessageBox::warning(this, "Warning", "You must select at least one row to plot.");
    }
    else
    {
        this->personalTimesPlot.plotTimes(personalTimes);
        this->personalTimesPlot.raise();
    }
}
