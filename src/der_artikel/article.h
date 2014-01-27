#ifndef ARTICLE_H
#define ARTICLE_H

#include <QObject>

/**
 * @brief
 *
 */
class Article_C : public QObject
{
    Q_OBJECT
    Q_ENUMS(Artikel)
    /**
     * @brief
     *
     * @param
     */
    Q_DISABLE_COPY(Article_C)
public:
    /**
     * @brief
     *
     */
    enum Artikel
    {
        DER = 1,
        DIE,
        DAS,
        NA,
        INVALID
    };

private:
    /**
     * @brief
     *
     * @param parent
     */
    explicit Article_C(QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @param artikel
     * @return QString
     */
    static QString ArtikelText(Article_C::Artikel artikel);
};

#endif // ARTICLE_H
