#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

#include <QColor>
#include <QHash>
#include "page.h"
#include "article.h"

class Word_C;

/**
 * @brief
 *
 */
class WordsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(bool info_mode READ infoMode WRITE setInfoMode NOTIFY infoModeChanged)
    Q_PROPERTY(Article_C::Artikel selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY selectedArticleChanged)

public:
    /**
     * @brief
     *
     * @param page_manager
     * @param root_context
     * @param parent
     */
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    /**
     * @brief
     *
     * @param prev_page_id
     */
    virtual void enter(Manager_C::PageId_TP prev_page_id);
    /**
     * @brief
     *
     * @param next_page_id
     */
    virtual void leave(Manager_C::PageId_TP next_page_id);

public:
    /**
     * @brief
     *
     * @return bool
     */
    bool infoMode() const { return _info_mode; }
    /**
     * @brief
     *
     * @param info_mode
     */
    void setInfoMode(bool info_mode);

    /**
     * @brief
     *
     * @param article
     */
    void SetSelectedArticle(Article_C::Artikel article);
    /**
     * @brief
     *
     * @return Article_C::Artikel
     */
    Article_C::Artikel GetSelectedArticle() const { return _selected_article; }

private slots:
    /**
     * @brief
     *
     */
    void OnWordClicked();

signals:
    /**
     * @brief
     *
     */
    void infoModeChanged();
    /**
     * @brief
     *
     */
    void selectedArticleChanged();

private:
    /**
     * @brief
     *
     * @param thema
     */
    void AddWords(const Thema_C *thema);
    /**
     * @brief
     *
     * @param text
     * @param desc
     * @return QObject
     */
    QObject* AddWord(QString text, QString desc);
    /**
     * @brief
     *
     */
    void ClearWordItems();
    /**
     * @brief
     *
     */
    void CreateResultAlgo();
    /**
     * @brief
     *
     */
    void CalculateResult();

private:
    QQmlContext& _root_context; /**< TODO */
    bool _info_mode; /**< TODO */
    QHash<QObject*, Word_C*> _item_word_hash; /**< TODO */
    Article_C::Artikel _selected_article; /**< TODO */
    ResultAlgo_I* _result_algo; /**< TODO */
};

#endif // WORDS_PAGE_H
