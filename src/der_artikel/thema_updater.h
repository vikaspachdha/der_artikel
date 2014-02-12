#ifndef THEMA_UPDATER_H
#define THEMA_UPDATER_H

#include <QObject>
#include <QUrl>
#include <QVector>
#include <QHash>

#include "file_downloader.h"

class ThemaUpdater_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(UpdateResponse_TP)
public:

    enum UpdateResponse_TP {
        UPDATE_AVAILABLE=1,
        UPDATE_NOT_AVAILABLE,
        UPDATE_ERROR
    };

    enum FileType_TP {
        IS_INDEX = 1,
        IS_THEMA,
        NONE
    };

    enum FileOperation_TP {
        ADD = 1,
        REPLACE,
        REMOVE,
    };

    struct FileOperationData_TP {
        public:
            QString _local_file_path;
            QUrl _remote_file_url;
            FileOperation_TP _operation;
    };

public:
    explicit ThemaUpdater_C(QObject *parent = 0);

public:
    void setRemoteThemaFolderUrl(QUrl url);

public:
    Q_INVOKABLE void checkUpdate(QString url_str);

private slots:
    void onFileDownloadFinished();
    void onFileDownloadAborted();

signals:
    void updateResponse(UpdateResponse_TP response_code);

private:
    bool ParseIndexFile(QByteArray file_data, QHash<QString, QDateTime>& parsed_data);
    bool createOperations(QHash<QString,QDateTime> parsed_data);
    bool executeOperations(QVector<FileOperationData_TP> _file_operations);

private:
    QUrl _remote_thema_folder_url;
    FileDownloader_C _file_downloader;
    FileType_TP _downloading_file_type;
};

#endif // THEMA_UPDATER_H
