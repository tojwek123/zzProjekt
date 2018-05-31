#include "datetimetablewidgetitem.h"

const char DateTimeTableWidgetItem::DateTimeFormat[] = "dd.MM.yyyy hh:mm:ss";

DateTimeTableWidgetItem::DateTimeTableWidgetItem(const QDateTime &dateTime) :
    QTableWidgetItem(dateTime.toString(DateTimeFormat))
{

}

bool DateTimeTableWidgetItem::operator<(const QTableWidgetItem &other) const
{
    /* Build temporary QDateTime objects */
    QDateTime myDateTime = QDateTime::fromString(this->text(), DateTimeFormat);
    QDateTime otherDateTime = QDateTime::fromString(other.text(), DateTimeFormat);

    bool result;

    if (myDateTime.isValid() && otherDateTime.isValid())
    {
        /* If time is valid use QDateTime comparison */
        result = myDateTime < otherDateTime;
    }
    else
    {
        /* Otherwise use default comparison */
        result = QTableWidgetItem::operator<(other);
    }

    return result;
}
