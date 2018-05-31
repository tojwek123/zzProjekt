#include "planracedialog.h"
#include "ui_planracedialog.h"

const char PlanRaceDialog::TimeFormat[] = "hh:mm:ss";

PlanRaceDialog::PlanRaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanRaceDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    this->setModal(true);

    connect(ui->calendar, &QCalendarWidget::clicked,
            this, &PlanRaceDialog::onCalendarClicked);

    connect(ui->timeList, &QListWidget::itemClicked,
            this, &PlanRaceDialog::onTimeListItemClicked);

    connect(ui->carList, &QListWidget::itemDoubleClicked,
            this, &PlanRaceDialog::onCarListItemDoubleClicked);

    connect(ui->okButton, &QPushButton::clicked,
            this, &PlanRaceDialog::onOkButtonClicked);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &PlanRaceDialog::onCancelButtonClicked);

    ui->calendar->setLocale(QLocale::English);
}

PlanRaceDialog::~PlanRaceDialog()
{
    delete ui;
}

void PlanRaceDialog::plan(const int userId)
{
    this->userId = userId;

    ui->timeList->clear();
    ui->carList->clear();

    ui->calendar->setMinimumDate(QDate::currentDate());

    DbConnection::getInstance().fetchAvailableDates(this->availableDateIds, this->availableDates);
    ui->calendar->setDates(this->availableDates);

    this->show();
}

void PlanRaceDialog::onCalendarClicked(const QDate &date)
{
    ui->timeList->clear();
    ui->carList->clear();
//    bool firstItem = true;

    for (int i = 0; i < this->availableDates.length(); ++i)
    {
        if (date == this->availableDates[i].date())
        {
            QListWidgetItem *pItem = new QListWidgetItem(this->availableDates[i].toString(TimeFormat));
            pItem->setData(Qt::UserRole, this->availableDateIds[i]);
            ui->timeList->addItem(pItem);
        }
    }
}

void PlanRaceDialog::onTimeListItemClicked(QListWidgetItem *pItem)
{
    QVector<int> carIds;
    QVector<QString> carBrands;
    QVector<QString> carModels;

    DbConnection::getInstance().fetchAvailableCars(pItem->data(Qt::UserRole).toInt(), carIds, carBrands, carModels);

    ui->carList->clear();

    for (int i = 0; i < carBrands.length(); ++i)
    {
        QListWidgetItem *pItem = new QListWidgetItem(carBrands[i] + " " + carModels[i]);
        pItem->setData(Qt::UserRole, carIds[i]);
        ui->carList->addItem(pItem);
    }
}

void PlanRaceDialog::onCarListItemDoubleClicked(QListWidgetItem*)
{
    this->onOkButtonClicked(true);
}

void PlanRaceDialog::onOkButtonClicked(bool)
{
    if (ui->calendar->selectedDate().isValid() &&
        ui->timeList->selectedItems().length() == 1U &&
        ui->carList->selectedItems().length() == 1U)
    {
        bool reservationDone = DbConnection::getInstance().reserveLap(ui->timeList->selectedItems()[0]->data(Qt::UserRole).toInt(),
                                                                      this->userId,
                                                                      ui->carList->selectedItems()[0]->data(Qt::UserRole).toInt());

        if (reservationDone)
        {
            emit raceReserved();
            this->hide();
        }
        else
        {
            QMessageBox::critical(this, "Error", "An error occurred during reservation");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "You must select date, time and car to reserve a race.");
    }
}

void PlanRaceDialog::onCancelButtonClicked(bool)
{
    this->hide();
}
