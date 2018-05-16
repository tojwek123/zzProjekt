#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QtSql>
#include <QCryptographicHash>

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
    bool fetchRacerLaps(const QString &racerName);

private:
    DbConnection();
    QSqlDatabase db;
};

#endif // DBCONNECTION_H
