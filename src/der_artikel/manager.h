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
class Settings_C;
class Page_I;

//class ThemaModel_C;

class Manager_C : public QObject
{
    Q_OBJECT

    Q_ENUMS(PageId_TP)
    Q_ENUMS(GameLevel)

    Q_PROPERTY(PageId_TP current_page READ getCurrentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(QAbstractItemModel* thema_model READ GetThemaModel CONSTANT)
    Q_PROPERTY(GameLevel game_level READ gameLevel WRITE setGameLevel NOTIFY gameLevelChanged)
    Q_PROPERTY(bool thema_selected READ isThemaSelected NOTIFY themaSelectionStateChanged)
    Q_PROPERTY(QString version_string READ versionString CONSTANT)

public:

    enum PageId_TP
    {
        HOME_PAGE =1,
        THEMA_PAGE,
        WORDS_PAGE,
        RESULT_PAGE,
        HELP_PAGE,
        STATS_PAGE,
        SETTINGS_PAGE,
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

    void setCurrentPage(PageId_TP new_page);
    PageId_TP getCurrentPage() const { return _current_page; }

    Result_C* GetCurrentResult() { return _current_result; }

    GameLevel gameLevel() const { return _game_level; }
    void setGameLevel(GameLevel game_level);

    bool isThemaSelected() const { return _thema_selected; }

    Q_INVOKABLE void showMessage();

    Q_INVOKABLE QString versionString() {return _version_string;}

public:
    ThemaModel_C* GetThemaModel() {return _thema_model; }

    Settings_C* GetSettings() const { return _settings; }

    Q_INVOKABLE void setPageItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* pageItem(PageId_TP page_id);

    Q_INVOKABLE void setPanelItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* panelItem(PageId_TP page_id);

    Q_INVOKABLE void setTitleItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* titleItem(PageId_TP page_id);

    Q_INVOKABLE void quit();

signals:
    void currentPageChanged(PageId_TP old_page, PageId_TP new_page);
    void gameLevelChanged();
    void themaSelectionStateChanged();
    
private slots:
    void OnNewThemaLoaded(Thema_C* new_thema);
    void onThemaSelectionChanged();

// Helper methods
private:
    void LoadDefaultThemas();
    void InitPages();

private:
    Settings_C* _settings;
    QQmlContext& _root_context;
    QQuickItem* _root_item;
    QHash<PageId_TP, PageItems_TP> _page_items_hash;
    QHash<PageId_TP, Page_I*> _page_hash;
    Thema_C* _current_thema;
    PageId_TP _current_page;
    Result_C* _current_result;
    ThemaModel_C* _thema_model;
    GameLevel _game_level;
    bool _thema_selected;
    QString _version_string;
};

#endif // MANAGER_H
