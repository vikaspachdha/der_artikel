#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

#include <QColor>
#include <QHash>
#include "page.h"
#include "article.h"

class Word_C;

class WordsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(bool info_mode READ infoMode WRITE setInfoMode NOTIFY infoModeChanged)
    Q_PROPERTY(Article_C::Artikel selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY selectedArticleChanged)
    Q_PROPERTY(QColor current_word_color READ GetCurrentWordColor)

public:
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, QObject *parent = 0);

public:
    virtual void enter();
    virtual void leave();

public:
    bool infoMode() const { return _info_mode; }
    void setInfoMode(bool info_mode);

    void SetSelectedArticle(Article_C::Artikel article);
    Article_C::Artikel GetSelectedArticle() const { return _selected_article; }

    QColor GetCurrentWordColor() const { return _current_word_color; }

private slots:
    void OnWordClicked();

signals:
    void infoModeChanged();
    void selectedArticleChanged();

private:
    void AddWords(const Thema_C *thema);
    QObject* AddWord(QString text, QString desc);
    void ClearWordItems();

private:
    QQmlContext& _root_context;
    bool _info_mode;
    QHash<QObject*, Word_C*> _item_word_hash;
    Article_C::Artikel _selected_article;
    QColor _current_word_color;
};

#endif // WORDS_PAGE_H
