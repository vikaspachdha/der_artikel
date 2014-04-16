#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

#include <QColor>
#include <QHash>
#include "page.h"
#include "data/article.h"

class Word_C;
class Settings_C;

class WordsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(bool info_mode READ infoMode WRITE setInfoMode NOTIFY infoModeChanged)
    Q_PROPERTY(Article_C::Artikel selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY selectedArticleChanged)

public:
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, Settings_C& settings, QObject *parent = 0);

public:
    virtual void enter(Manager_C::PageId_TP prev_page_id);
    virtual void leave(Manager_C::PageId_TP next_page_id);

public:
    bool infoMode() const { return _info_mode; }
    void setInfoMode(bool info_mode);

    void SetSelectedArticle(Article_C::Artikel article);
    Article_C::Artikel GetSelectedArticle() const { return _selected_article; }

private slots:
    void OnWordClicked();

signals:
    void infoModeChanged();
    void selectedArticleChanged();

private:
    void AddWords(const Thema_C *thema, bool practice_mode=false);
    QObject* AddWord(Word_C &word);
    void ClearWordItems();
    void CreateResultAlgo();
    void CalculateResult();

private:
    QQmlContext& _root_context;
    Settings_C& _settings;
    bool _info_mode;
    QHash<QObject*, Word_C*> _item_word_hash;
    Article_C::Artikel _selected_article;
    ResultAlgo_I* _result_algo;
};

#endif // WORDS_PAGE_H
