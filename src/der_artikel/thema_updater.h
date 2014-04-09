#ifndef THEMA_UPDATER_H
#define THEMA_UPDATER_H

#include <QObject>
#include <QUrl>
#include <QVector>
#include <QHash>

#include "file_downloader.h"

class Thema_C;
class Manager_C;
class ThemaFileOperation_I;

class ThemaUpdater_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(UpdateResponse_TP)
public:

    enum UpdateResponse_TP {
        UPDATE_AVAILABLE=1,
        UPDATE_NOT_AVAILABLE,
        UPDATE_ERROR,
        UPDATE_FINISHED
    };

public:
    explicit ThemaUpdater_C(Manager_C& manager, QObject *parent = 0);

public:
    Q_INVOKABLE void checkUpdate();

private slots:
    void onFileDownloadFinished();
    void onFileDownloadAborted();
    void onNewthemaLoaded(Thema_C *new_thema);
    void onBuildLocalDataFinished();

signals:
    void updateResponse(UpdateResponse_TP response_code);

private:
    bool ParseIndexFile(QByteArray file_data, QHash<QString, QDateTime>& parsed_data);
    bool executeOperations();
    void buildLocalData();
    void reset();

private:
    Manager_C& _manager;
    FileDownloader_C _file_downloader;
    QHash<QString, QDateTime> _remote_file_data;
    QVector<ThemaFileOperation_I*> _file_operations;
};

#endif // THEMA_UPDATER_H
