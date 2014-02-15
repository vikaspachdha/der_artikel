#include "thema_delete_operation.h"
#include <QFile>

ThemaDeleteOperation_C::ThemaDeleteOperation_C(QString local_file_path):
    QObject(0),
    _local_file_path(local_file_path)
{
}

bool ThemaDeleteOperation_C::execute()
{
    return QFile::remove(_local_file_path);
}
