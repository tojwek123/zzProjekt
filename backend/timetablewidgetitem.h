#ifndef TIMETABLEWIDGETITEM_H
#define TIMETABLEWIDGETITEM_H

#include <QTableWidgetItem>
#include <QTime>

class TimeTableWidgetItem : public QTableWidgetItem
{
private:
    static const char TimeFormat[];

public:
    TimeTableWidgetItem(const QTime &time);

    virtual bool operator<(const QTableWidgetItem &other) const;
};

#endif // TIMETABLEWIDGETITEM_H
