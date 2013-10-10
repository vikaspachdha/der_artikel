#include "common.h"
#include <QCoreApplication>
#include <QFileInfo>

namespace ARTIKEL{

QString ArtikelText(Artikel artikel)
{
    QString text;
    switch(artikel)
    {
    case DER:
        text = "Der";
        break;

    case DIE:
        text = "Die";
        break;

    case DAS:
        text = "Das";
        break;

    default:
        text = "";
        break;

    }

    return text;
}

QString GetResourcePath(const QString &path)
{
#if defined(Q_OS_MAC)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("%1/../Resources/%2")
                .arg(QCoreApplication::applicationDirPath(), path);
#elif defined(Q_OS_BLACKBERRY)
    if (!QDir::isAbsolutePath(path))
        return QString::fromLatin1("app/native/%1").arg(path);
#elif !defined(Q_OS_ANDROID)
    QString pathInInstallDir =
            QString::fromLatin1("%1/../%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
    pathInInstallDir =
            QString::fromLatin1("%1/%2").arg(QCoreApplication::applicationDirPath(), path);
    if (QFileInfo(pathInInstallDir).exists())
        return pathInInstallDir;
#endif
    return path;
}

}
