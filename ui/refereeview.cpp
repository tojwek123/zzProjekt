#include "refereeview.h"
#include "ui_refereeview.h"

RefereeView::RefereeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RefereeView)
{
    ui->setupUi(this);

    connect(ui->racesTable, QTableWidget::itemClicked,
            this, RefereeView::onRacesTableItemClicked);

    connect(ui->closeRaceButton, QPushButton::clicked,
            this, RefereeView::onCloseRaceButtonClicked);

    QStringList racesTableColumnHeaders;
    racesTableColumnHeaders.append("Date");
    racesTableColumnHeaders.append("Number of racers");

    ui->racesTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->racesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->racesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->racesTable->setColumnCount(racesTableColumnHeaders.length());
    ui->racesTable->setHorizontalHeaderLabels(racesTableColumnHeaders);

    QStringList participantsTableColumnHeaders;
    participantsTableColumnHeaders.append("Name");
    participantsTableColumnHeaders.append("Time");

    ui->participantsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->participantsTable->setColumnCount(participantsTableColumnHeaders.length());
    ui->participantsTable->setHorizontalHeaderLabels(participantsTableColumnHeaders);
    ui->participantsTable->setSortingEnabled(false);

    updateRaceTable();
}

RefereeView::~RefereeView()
{
    delete ui;
}

void RefereeView::updateRaceTable()
{
    QVector<int> ids;
    QVector<QDateTime> dates;

    DbConnection::getInstance().fetchAvailableDates(ids, dates);
    ui->racesTable->setSortingEnabled(false);
    ui->racesTable->setRowCount(ids.length());

    for (int i = 0; i < ids.length(); ++i)
    {
        DateTimeTableWidgetItem *pDateItem = new DateTimeTableWidgetItem(dates[i]);

        QVector<int> userIds;
        QVector<QString> userNames;
        DbConnection::getInstance().fetchRaceParticipants(ids[i], userIds, userNames);

        pDateItem->setTextAlignment(Qt::AlignCenter);
        pDateItem->setData(Qt::UserRole, ids[i]);

        QTableWidgetItem *pRacersCountItem = new QTableWidgetItem(QString::number(userIds.length()));
        pRacersCountItem->setTextAlignment(Qt::AlignCenter);

        ui->racesTable->setItem(i, 0, pDateItem);
        ui->racesTable->setItem(i, 1, pRacersCountItem);
    }

    ui->racesTable->setSortingEnabled(true);
}

void RefereeView::onRacesTableItemClicked(QTableWidgetItem*)
{
    int currentRow = ui->racesTable->currentRow();
    int dateId = ui->racesTable->item(currentRow, 0)->data(Qt::UserRole).toInt();

    QVector<int> userIds;
    QVector<QString> userNames;

    DbConnection::getInstance().fetchRaceParticipants(dateId, userIds, userNames);
    ui->participantsTable->setRowCount(userIds.length());

    for (int i = 0; i < userIds.length(); ++i)
    {
        QTableWidgetItem *pNameItem = new QTableWidgetItem(userNames[i]);
        pNameItem->setTextAlignment(Qt::AlignCenter);
        pNameItem->setData(Qt::UserRole, userIds[i]);

        QTableWidgetItem *pTimeItem = new QTableWidgetItem();
        QTimeEdit *pTimeEdit = new QTimeEdit();
        pTimeEdit->setDisplayFormat("mm:ss.zzz");

        ui->participantsTable->setItem(i, 0, pNameItem);
        ui->participantsTable->setItem(i, 1, pTimeItem);
        ui->participantsTable->setCellWidget(i, 1, pTimeEdit);
    }
}

void RefereeView::onCloseRaceButtonClicked(bool)
{
    if (0 == ui->racesTable->rowCount())
    {
        return;
    }

    if (0 == ui->participantsTable->rowCount())
    {
        if (QMessageBox::Yes != QMessageBox::warning(this, "Warning", "Do you really want to close race with no participants?", QMessageBox::Yes, QMessageBox::No))
        {
            return;
        }
    }

    int dateId = ui->racesTable->item(ui->racesTable->currentRow(), 0)->data(Qt::UserRole).toInt();

    for (int i = 0; i < ui->participantsTable->rowCount(); ++i)
    {
        int userId = ui->participantsTable->item(i, 0)->data(Qt::UserRole).toInt();
        QTime time = reinterpret_cast<QTimeEdit*>(ui->participantsTable->cellWidget(i, 1))->time();

        if (time == QTime(0, 0, 0))
        {
            QMessageBox::warning(this, "Warning", "Lap time must be greater than zero");
            return;
        }

        DbConnection::getInstance().setLapTimes(userId, time, dateId);
    }

    DbConnection::getInstance().deleteRaceReservationsByDateId(dateId);
    DbConnection::getInstance().deleteAvailableDate(dateId);

    ui->participantsTable->setRowCount(0);

    this->updateRaceTable();
}
