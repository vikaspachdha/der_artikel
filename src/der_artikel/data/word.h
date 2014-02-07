#ifndef WORD_H
#define WORD_H
#include "article.h"
#include <QDomElement>
#include <QObject>

/**
 * @brief
 *
 */
class Word_C : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString word_text READ GetWordText CONSTANT)
    Q_PROPERTY(Article_C::Artikel user_article READ GetUserArtikel NOTIFY userArticleChanged)
    Q_PROPERTY(Article_C::Artikel article READ GetArtikel CONSTANT)

public:
/**
 * @brief
 *
 * @param parent
 */
    Word_C(QObject* parent=0);

public:
    /**
     * @brief
     *
     * @param article
     */
    void SetUserArtikel(Article_C::Artikel article);
    /**
     * @brief
     *
     * @return Article_C::Artikel
     */
    Article_C::Artikel GetUserArtikel() const { return _user_artikel; }

    /**
     * @brief
     *
     * @return Article_C::Artikel
     */
    Article_C::Artikel GetArtikel() const { return _artikel; }

    /**
     * @brief
     *
     * @return QString
     */
    QString GetWordText() const { return _text; }

    /**
     * @brief
     *
     * @return QString
     */
    QString GetDescription() const  { return _description; }

public:
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Read(const QDomElement& element);
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Write(QDomElement& element);
    /**
     * @brief
     *
     * @return bool
     */
    bool IsCorrect() const;

signals:
    void userArticleChanged();

private:
    QString _text; /**< TODO */
    QString _description; /**< TODO */
    Article_C::Artikel _artikel; /**< TODO */
    Article_C::Artikel _user_artikel; /**< TODO */

private:
    friend class ThemaBuilder_C;
};
#endif // WORD_H
