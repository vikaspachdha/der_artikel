#ifndef COMMON_H
#define COMMON_H

#include <QString>

namespace ARTIKEL
{
    static const int COMPRESSION_LEVEL = 5; /**< TODO */
    /**
     * @brief
     *
     * @param path
     * @return QString
     */
    QString GetResourcePath(const QString &path);
}
#endif // COMMON_H
