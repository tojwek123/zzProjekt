#include "dbconnection.h"

const char DbConnection::DbTimeFormat[] = "hh:mm:ss.zzz";
const char DbConnection::DbDateTimeFormat[] = "yyyy-MM-ddThh:mm:ss";


DbConnection::DbConnection()
{
    this->db = QSqlDatabase::addDatabase("QODBC");
}

DbConnection & DbConnection::getInstance()
{
    static DbConnection instance;
    return instance;
}

bool DbConnection::connect()
{
    this->db.setDatabaseName("DRIVER={SQL SERVER};SERVER=DESKTOP-B6KDFI4\\SQLEXPRESS;DATABASE=trackDay;");
    return this->db.open();
}

void DbConnection::disconnect()
{
    this->db.close();
}

bool DbConnection::validateLogin(const int type, const QString &name, const QString &password)
{
    bool loginValid = false;

    QByteArray calculatedHash = QCryptographicHash::hash(QString(password).toUtf8(), QCryptographicHash::Sha1).toHex();

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT passwordSha1 FROM users WHERE typeId = %1 AND name = '%2'").arg(type).arg(name);
    query.prepare(queryStr);

    if (query.exec())
    {
        /* Query executed successfully */

        if (query.first())
        {
            /* Sha1 was retrieved */
            QByteArray retrievedHash = query.value(0).toByteArray();

            if (retrievedHash == calculatedHash)
            {
                /* Login is only valid when hashes are the same */
                loginValid = true;
            }
        }
    }

    return loginValid;
}

bool DbConnection::fetchRacerLaps(const int userId, QVector<QTime> &durations, QVector<QDateTime> &dates)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT laps.duration, laps.startDateTime FROM laps INNER JOIN users on %1 = users.id ORDER BY laps.duration").arg(userId);
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            durations.clear();
            dates.clear();

            do
            {
                durations.append(QTime::fromString(query.value(0).toString(), DbTimeFormat));
                dates.append(QDateTime::fromString(query.value(1).toString(), DbDateTimeFormat));
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::fetchLeaderboard(QVector<QString> &names, QVector<QTime> &durations, QVector<QDateTime> &dates)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT users.name, laps.duration, laps.startDateTime FROM laps INNER JOIN users ON laps.userId = users.id ORDER BY laps.duration");
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            names.clear();
            durations.clear();
            dates.clear();

            do
            {
                names.append(query.value(0).toString());
                durations.append(QTime::fromString(query.value(1).toString(), DbTimeFormat));
                dates.append(QDateTime::fromString(query.value(2).toString(), DbDateTimeFormat));
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::fetchAvailableDates(QVector<int> &ids, QVector<QDateTime> &dates)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT id, date FROM availableDates");
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            ids.clear();
            dates.clear();

            do
            {
                ids.append(query.value(0).toInt());
                dates.append(QDateTime::fromString(query.value(1).toString(), DbDateTimeFormat));
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::fetchAvailableCars(const int dateId, QVector<int> &carIds, QVector<QString> &carBrands, QVector<QString> &carModels)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("EXEC getAvailableCars %1").arg(dateId);
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            carIds.clear();
            carBrands.clear();
            carModels.clear();

            do
            {
                carIds.append(query.value(0).toInt());
                carBrands.append(query.value(1).toString());
                carModels.append(query.value(2).toString());
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::fetchReservedLaps(const int userId, QVector<int> &reservedLapIds, QVector<QDateTime> &dates, QVector<QString> &carBrands, QVector<QString> &carModels)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("EXEC getReservedLapsPretty %1").arg(userId);
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            reservedLapIds.clear();
            dates.clear();
            carBrands.clear();
            carModels.clear();

            do
            {
                reservedLapIds.append(query.value(0).toInt());
                dates.append(query.value(1).toDateTime());
                carBrands.append(query.value(2).toString());
                carModels.append(query.value(3).toString());
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::reserveLap(const int dateId, const int userId, const int carId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("INSERT INTO reservedLaps VALUES(%1, %2, %3)").arg(dateId).arg(userId).arg(carId);
    query.prepare(queryStr);

    return query.exec();;
}

bool DbConnection::cancelRaceReservation(const int reservedLapId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("DELETE FROM reservedLaps WHERE id = %1").arg(reservedLapId);
    query.prepare(queryStr);

    return query.exec();;
}
