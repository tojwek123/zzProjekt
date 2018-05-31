#ifndef SPECIFICDATESCALENDAR_H
#define SPECIFICDATESCALENDAR_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDate>
#include <QDateTime>
#include <QDebug>
#include <QPainter>

class SpecificDatesCalendar : public QCalendarWidget
{
public:
    explicit SpecificDatesCalendar(QWidget *parent=0);

    void setDates(const QVector<QDate> &dates);
    void setDates(const QVector<QDateTime> &dateTimes);

private:
    QVector<QDate> dates;

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;
};

#endif // SPECIFICDATESCALENDAR_H
