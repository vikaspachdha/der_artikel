#ifndef THEMA_LOADER_H
#define THEMA_LOADER_H

#include <QObject>
#include <QString>
#include <QRunnable>

class Thema_C;

class ThemaLoader_C: public QObject, public QRunnable
{
    Q_OBJECT
public:
    ThemaLoader_C(QObject* thema_parent=0, QObject* parent = 0);

protected:
    virtual void run();

public:
    Thema_C* LoadThema(QString file_path);
    void StartLoading();

signals:
    void ThemaLoaded(Thema_C* new_thema);
    void finishedLoading();
private:

    QString _root_dir;
    QObject* _thema_parent;
};

#endif // THEMA_LOADER_H
