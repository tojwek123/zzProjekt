#include "dbconnection.h"

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

bool DbConnection::fetchRacerLaps(const QString &racerName)
{
//    QString queryStr = QString("SE")
    return false;
}
