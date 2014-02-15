#ifndef THEMA_DELETE_OPERATION_H
#define THEMA_DELETE_OPERATION_H

#include <QObject>
#include "thema_file_operation.h"

class ThemaDeleteOperation_C : public QObject, public ThemaFileOperation_I
{
public:
    ThemaDeleteOperation_C(QString local_file_path);

public:
    virtual bool execute();

private:
    QString _local_file_path;
};

#endif // THEMA_DELETE_OPERATION_H
