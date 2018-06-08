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

    bool fetchUserId(const QString &userName, int &userId);
    bool fetchRacerLaps(const int userId, QVector<QTime> &durations, QVector<QDateTime> &dates);
    bool fetchLeaderboard(QVector<QString> &names, QVector<QTime> &durations, QVector<QDateTime> &dates);
    bool fetchAvailableDates(QVector<int> &ids, QVector<QDateTime> &dates);
    bool fetchAvailableCars(const int dateId, QVector<int> &carIds, QVector<QString> &carBrands, QVector<QString> &carModels);
    bool fetchReservedLaps(const int userId, QVector<int> &reservedLapIds, QVector<QDateTime> &dates, QVector<QString> &carBrands, QVector<QString> &carModels);
    bool fetchRaceParticipants(const int dateId, QVector<int> &userIds, QVector<QString> &userNames);
    bool fetchUserDetails(const int userId, QString &userName, QString &firstName, QString &secondName);
    bool fetchUserType(const QString &userName, int &userType);

    bool validateLogin(const QString &name, const QString &password);
    bool changePassword(const int userId, const QString &password);
    bool reserveLap(const int dateId, const int userId, const int carId);
    bool deleteRaceReservation(const int reservedLapId);
    bool deleteRaceReservationsByDateId(const int dateId);
    bool setLapTimes(const int userId, const QTime &time, const int dateId);
    bool deleteAvailableDate(const int dateId);
    bool updateUserDetails(const int userId, const QString &firstName, const QString &secondName);
    bool addRaceDate(const QDateTime &date);

private:
    DbConnection();
    QSqlDatabase db;

    static const char DbTimeFormat[];
    static const char DbDateTimeFormat[];
};

#endif // DBCONNECTION_H
