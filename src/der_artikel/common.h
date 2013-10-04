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
}
#endif // COMMON_H
