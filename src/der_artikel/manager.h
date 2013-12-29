#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QColor>
#include "data/result.h"
#include "article.h"
#include "thema_model.h"

class QQuickItem;
class Thema_C;
class Word_C;
class ResultAlgo_I;
class QQuickItem;
class QQmlContext;
class Page_I;

//class ThemaModel_C;

class Manager_C : public QObject
{
    Q_OBJECT

    Q_ENUMS(PageId_TP)
    Q_ENUMS(GameLevel)

    Q_PROPERTY(Article_C::Artikel selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY selectedArticleChanged)
    Q_PROPERTY(QColor current_word_color READ GetCurrentWordColor)
    Q_PROPERTY(PageId_TP current_page READ getCurrentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(QAbstractItemModel* thema_model READ GetThemaModel CONSTANT)
    Q_PROPERTY(GameLevel game_level READ gameLevel WRITE setGameLevel NOTIFY gameLevelChanged)
    Q_PROPERTY(bool thema_selected READ isThemaSelected NOTIFY themaSelectionStateChanged)

public:



    enum PageId_TP
    {
        HOME_PAGE =1,
        THEMA_PAGE,
        WORDS_PAGE,
        RESULT_PAGE,
        HELP_PAGE,
        STATS_PAGE,
        PREF_PAGE,
        ABOUT_PAGE,
        INVALID_PAGE
    };

    enum GameLevel {
        EASY=1,
        MODERATE,
        EXPERT
    };

private:
    struct PageItems_TP {
        PageItems_TP() :
            _page_item(0),
            _panel_item(0),
            _title_item(0){}
        QQuickItem* _page_item;
        QQuickItem* _panel_item;
        QQuickItem* _title_item;
    };

public:
    explicit Manager_C(QQmlContext &ref_root_context, QObject *parent = 0);
    ~Manager_C();
    
public:
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

    void SetSelectedArticle(Article_C::Artikel article);
    Article_C::Artikel GetSelectedArticle() const { return _selected_article; }

    QColor GetCurrentWordColor() const { return _current_word_color; }

    void setCurrentPage(PageId_TP new_page);
    PageId_TP getCurrentPage() const { return _current_page; }

    ResultAlgo_I* resultAlgo() { return _result_algo; }

    Result_C* GetCurrentResult() { return _current_result; }

    GameLevel gameLevel() const { return _game_level; }
    void setGameLevel(GameLevel game_level);

    bool isThemaSelected() const { return _thema_selected; }

public:
    void CalculateResult();
    ThemaModel_C* GetThemaModel() {return _thema_model; }

    Q_INVOKABLE void setPageItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* pageItem(PageId_TP page_id);

    Q_INVOKABLE void setPanelItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* panelItem(PageId_TP page_id);

    Q_INVOKABLE void setTitleItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* titleItem(PageId_TP page_id);

signals:
    void selectedArticleChanged();
    void currentPageChanged(PageId_TP old_page, PageId_TP new_page);
    void gameLevelChanged();
    void themaSelectionStateChanged();
    void newResultAvailable();
    
private slots:
    void OnNewThemaLoaded(Thema_C* new_thema);
    void OnSelectedArticleChanged();
    void OnWordClicked();
    void onThemaSelectionChanged();

// Helper methods
private:
    void LoadDefaultThemas();
    void SetCurrentThema(Thema_C* thema);
    void AddWords(const Thema_C *thema);
    QObject* AddWord(QString text);
    void ClearWordItems();
    void CreateResultAlgo();
    void InitPages();

private:
    QQmlContext& _root_context;
    QQuickItem* _root_item;
    QHash<QObject*, Word_C*> _item_word_hash;
    QHash<PageId_TP, PageItems_TP> _page_items_hash;
    QHash<PageId_TP, Page_I*> _page_hash;
    Thema_C* _current_thema;
    Article_C::Artikel _selected_article;
    QColor _current_word_color;
    PageId_TP _current_page;
    ResultAlgo_I* _result_algo;
    Result_C* _current_result;
    ThemaModel_C* _thema_model;
    GameLevel _game_level;
    bool _thema_selected;
};

#endif // MANAGER_H
