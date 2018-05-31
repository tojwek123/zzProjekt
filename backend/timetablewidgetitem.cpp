#include "timetablewidgetitem.h"
#include <QDebug>
const char TimeTableWidgetItem::TimeFormat[] = "mm:ss:zzz";

TimeTableWidgetItem::TimeTableWidgetItem(const QTime &time) :
    QTableWidgetItem(time.toString(TimeFormat))
{

}

bool TimeTableWidgetItem::operator<(const QTableWidgetItem &other) const
{
    /* Build temporary QTime objects */
    QTime myTime = QTime::fromString(this->text(), TimeFormat);
    QTime otherTime = QTime::fromString(other.text(), TimeFormat);

    bool result;

    if (myTime.isValid() && otherTime.isValid())
    {
        /* If time is valid use QTime comparison */
        result = myTime < otherTime;
    }
    else
    {
        /* Otherwise use default comparison */
        result = QTableWidgetItem::operator<(other);
    }

    return result;
}
