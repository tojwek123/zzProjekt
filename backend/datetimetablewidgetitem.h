#ifndef DATETIMETABLEWIDGETITEM_H
#define DATETIMETABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <QDateTime>

class DateTimeTableWidgetItem : public QTableWidgetItem
{
private:
    static const char DateTimeFormat[];

public:
    DateTimeTableWidgetItem(const QDateTime &dateTime);

    virtual bool operator<(const QTableWidgetItem &other) const;
};

#endif // DATETIMETABLEWIDGETITEM_H
