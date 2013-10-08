#ifndef THEMA_LOADER_H
#define THEMA_LOADER_H

#include <QObject>
#include <QString>

class Thema_C;

class ThemaLoader_C: public QObject
{
    Q_OBJECT
public:
    ThemaLoader_C(QObject* parent = 0);

public:
    Thema_C* LoadThema(QString file_path);


private:

    QString _root_dir;
};

#endif // THEMA_LOADER_H
