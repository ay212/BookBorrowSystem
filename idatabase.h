#ifndef IDATABASE_H
#define IDATABASE_H

#include <QObject>

class IDatabase : public QObject
{
    Q_OBJECT
public:
    explicit IDatabase(QObject *parent = nullptr);

signals:
};

#endif // IDATABASE_H
