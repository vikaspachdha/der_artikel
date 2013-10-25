#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QColor>
#include "common.h"

class QQuickItem;
class Thema_C;
class Word_C;

class Manager_C : public QObject
{
    Q_OBJECT

    Q_ENUMS(PageType)

    Q_PROPERTY(uint selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY selectedArticleChanged)
    Q_PROPERTY(QColor current_word_color READ GetCurrentWordColor)
    Q_PROPERTY(PageType current_page READ GetCurrentPage WRITE SetCurrentPage NOTIFY currentPageChanged)

public:
    enum PageType
    {
        HOME_PAGE =1,
        THEMA_PAGE,
        WORDS_PAGE,
        RESULT_PAGE,
        STATS_PAGE,
        PREF_PAGE,
        ABOUT_PAGE
    };

public:
    explicit Manager_C(QObject *parent = 0);
    ~Manager_C();
    
public:
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

    void SetSelectedArticle(uint article);
    uint GetSelectedArticle() const { return (uint)_selected_article; }

    QColor GetCurrentWordColor() const { return _current_word_color; }

    void SetCurrentPage(PageType new_page);
    PageType GetCurrentPage() const { return _current_page; }


public:
    Q_INVOKABLE void showResult();

signals:
    void selectedArticleChanged();
    void currentPageChanged(PageType old_page, PageType new_page);
    
private slots:
    void OnNewThemaLoaded(Thema_C* new_thema);
    void OnSelectedArticleChanged();
    void OnWordClicked();

// Helper methods
private:
    void LoadDefaultThemas();
    void SetCurrentThema(Thema_C* thema);
    void AddWords(const Thema_C *thema);
    QObject* AddWord(QString text);
    void ClearWordItems();

private:
    QQuickItem* _root_item;
    QVector<Thema_C*> _themas;
    QHash<QObject*, Word_C*> _item_word_hash;
    Thema_C* _current_thema;
    ARTIKEL::Artikel _selected_article;
    QColor _current_word_color;
    PageType _current_page;
};

#endif // MANAGER_H
