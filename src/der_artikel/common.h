#ifndef COMMON_H
#define COMMON_H

#include <QString>

namespace ARTIKEL
{
    enum Artikel
    {
        DER,
        DIE,
        DAS,
        NA,
        INVALID
    };

    QString ArtikelText(Artikel artikel);

    QString GetResourcePath(const QString &path);

}
#endif // COMMON_H
