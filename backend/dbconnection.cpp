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

bool DbConnection::fetchUserId(const QString &userName, int &userId)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT id FROM users WHERE name = '%1'").arg(userName);
    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            userId = query.value(0).toInt();
            ok = true;
        }
    }

    return ok;
}

bool DbConnection::validateLogin(const QString &name, const QString &password)
{
    bool loginValid = false;

    QByteArray calculatedHash = QCryptographicHash::hash(QString(password).toUtf8(), QCryptographicHash::Sha1).toHex();

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT passwordSha1 FROM users WHERE name = '%1'").arg(name);
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

bool DbConnection::changePassword(const int userId, const QString &password)
{
    QByteArray hash = QCryptographicHash::hash(QString(password).toUtf8(), QCryptographicHash::Sha1).toHex();

    QSqlQuery query(this->db);
    QString queryStr = QString("UPDATE users SET passwordSha1='%1' WHERE id = %2").arg(QString(hash)).arg(userId);
    query.prepare(queryStr);

    return query.exec();
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

bool DbConnection::fetchRaceParticipants(const int dateId, QVector<int> &userIds, QVector<QString> &userNames)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("\
SELECT users.id, users.name, reservedLaps.carId FROM reservedLaps \
INNER JOIN users ON users.id  = reservedLaps.userId \
WHERE reservedLaps.dateId = %1\
ORDER BY users.name").arg(dateId);

    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            userIds.clear();
            userNames.clear();

            do
            {
                userIds.append(query.value(0).toInt());
                userNames.append(query.value(1).toString());
            } while (query.next());

            ok = true;
        }
    }

    return ok;
}

bool DbConnection::fetchUserDetails(const int userId, QString &userName, QString &firstName, QString &secondName)
{
    bool ok = false;

    QSqlQuery query(this->db);
    QString queryStr = QString("SELECT name, firstName, secondName FROM users WHERE id = %1").arg(userId);

    query.prepare(queryStr);

    if (query.exec())
    {
        if (query.first())
        {
            do
            {
                userName = query.value(0).toString();
                firstName = query.value(1).toString();
                secondName = query.value(2).toString();
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

    return query.exec();
}

bool DbConnection::deleteRaceReservation(const int reservedLapId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("DELETE FROM reservedLaps WHERE id = %1").arg(reservedLapId);
    query.prepare(queryStr);

    return query.exec();
}

bool DbConnection::deleteRaceReservationsByDateId(const int dateId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("DELETE FROM reservedLaps WHERE dateId = %1").arg(dateId);
    query.prepare(queryStr);

    return query.exec();
}

bool DbConnection::setLapTimes(const int userId, const QTime &time, const int dateId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("INSERT INTO laps SELECT %1, '%2', (SELECT date FROM availableDates WHERE id = %3), (SELECT carId FROM reservedLaps WHERE dateId = %3 AND userId = %1)").arg(userId).arg(time.toString(DbTimeFormat)).arg(dateId);
    query.prepare(queryStr);

    return query.exec();
}

bool DbConnection::deleteAvailableDate(const int dateId)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("DELETE FROM availableDates WHERE id = %1").arg(dateId);
    query.prepare(queryStr);

    return query.exec();
}

bool DbConnection::updateUserDetails(const int userId, const QString &firstName, const QString &secondName)
{
    QSqlQuery query(this->db);
    QString queryStr = QString("UPDATE users SET firstName='%1', secondName='%2' WHERE id = %3").arg(firstName).arg(secondName).arg(userId);
    query.prepare(queryStr);

    return query.exec();
}
