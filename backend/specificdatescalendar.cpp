#include "specificdatescalendar.h"

SpecificDatesCalendar::SpecificDatesCalendar(QWidget *parent) : QCalendarWidget(parent)
{

}

void SpecificDatesCalendar::setDates(const QVector<QDate> &dates)
{
    this->dates = dates;
    this->repaint();
}

void SpecificDatesCalendar::setDates(const QVector<QDateTime> &dateTimes)
{
    this->dates.clear();

    for (auto i : dateTimes)
    {
        if (i > QDateTime::currentDateTime())
        {
            this->dates.append(i.date());
        }
    }

    this->repaint();
}


void SpecificDatesCalendar::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    QCalendarWidget::paintCell(painter, rect, date);

    if (this->dates.contains(date))
    {
        //painter->setBrush(QBrush(QColor(128, 128, 255, 32)));
        painter->setPen(QColor(Qt::black));
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
}
