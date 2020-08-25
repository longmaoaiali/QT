#ifndef CONNECTIONH_H
#define CONNECTIONH_H

#include <QtSql>
#include <QtDebug>
#include <QString>
#include <QCoreApplication>


class connectionh
{
public:
    static QString dataPath;
    connectionh();
    static bool createConnection();
    static bool createDailyXml();
};

#endif // CONNECTIONH_H
