#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>
#include <QCryptographicHash>
#include <QDateTime>
#include <QTime>
#include <QDateTime>

struct LapInfo
{
    QString racerName;
    int racerID;
    QString carName;
    int carID;
    QTime time;
};

class DbConnection
{
public:
    DbConnection(DbConnection const&) = delete;
    void operator=(DbConnection const&) = delete;

    static DbConnection &getInstance();
    bool connect();
    void disconnect();

    bool validateLogin(const int type, const QString &name, const QString &password);
    bool fetchRacerLaps(const int userId, QVector<QTime> &durations, QVector<QDateTime> &dates);
    bool fetchLeaderboard(QVector<QString> &names, QVector<QTime> &durations, QVector<QDateTime> &dates);
    bool fetchAvailableDates(QVector<int> &ids, QVector<QDateTime> &dates);
    bool fetchAvailableCars(const int dateId, QVector<int> &carIds, QVector<QString> &carBrands, QVector<QString> &carModels);
    bool fetchReservedLaps(const int userId, QVector<int> &reservedLapIds, QVector<QDateTime> &dates, QVector<QString> &carBrands, QVector<QString> &carModels);

    bool reserveLap(const int dateId, const int userId, const int carId);
    bool cancelRaceReservation(const int reservedLapId);

private:
    DbConnection();
    QSqlDatabase db;

    static const char DbTimeFormat[];
    static const char DbDateTimeFormat[];
};

#endif // DBCONNECTION_H
