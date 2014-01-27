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
class ImageProvider_C;
class Thema_C;
class Word_C;
class ResultAlgo_I;
class QQuickItem;
class QQmlContext;
class Settings_C;
class Page_I;

//class ThemaModel_C;

/**
 * @brief
 *
 */
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

    /**
     * @brief Pages id's. Every page has an unique id.
     *
     */
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

    /**
     * @brief Game levels. A user can choose between these levels to play game.
     * Different levels define different scoring and time to play the game.
     */
    enum GameLevel {
        EASY=1,
        MODERATE,
        EXPERT
    };

private:
    /**
     * @brief Each page has a panel item for hosting commands and a main display
     * item called page item and a title item to show extra information.
     */
    struct PageItems_TP {
/**
 * @brief Constructor
 *
 */
        PageItems_TP() :
            _page_item(0),
            _panel_item(0),
            _title_item(0){}
        QQuickItem* _page_item; /**< TODO */
        QQuickItem* _panel_item; /**< TODO */
        QQuickItem* _title_item; /**< TODO */
    };

public:
    /**
     * @brief Main manager class responsible for workflow and pivot for exposing data models to UI.
     *
     * @param ref_root_context The root qml context.
     * @param parent Parent object instance
     */
    explicit Manager_C(QQmlContext &ref_root_context, QObject *parent = 0);

    /**
     * @brief Destructor
     *
     */
    ~Manager_C();
    
public:
    /**
     * @brief Sets the root qml Item. i.e the main item.
     *
     * @param root_Item
     */
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

    /**
     * @brief Changes the current page displayed on the ui. Call this method to change the page.
     * The page will only be changed if the conditions are met for the last page to leave and
     * new page to enter.
     *
     * @param new_page The id of the new page to show.
     */
    void setCurrentPage(PageId_TP new_page);

    /**
     * @brief Returns the id of the current page visible.
     *
     * @return PageId_TP @ref PageId_TP of current page.
     */
    PageId_TP getCurrentPage() const { return _current_page; }

    /**
     * @brief Returns the current result instance. The instance stores the result data
     * of the las game played and the instance is updated as soon as user finished a game.
     *
     * @return Result_C
     */
    Result_C* GetCurrentResult() { return _current_result; }

    /**
     * @brief Returns the current game level selected.
     *
     * @return GameLevel The current @ref GameLevel selected.
     */
    GameLevel gameLevel() const { return _game_level; }

    /**
     * @brief Sets the game level.
     *
     * @param game_level The new game level.
     */
    void setGameLevel(GameLevel game_level);

    /**
     * @brief Returns state of thema selection.
     *
     * @return bool True if a thema selection is available, false otherwise.
     */
    bool isThemaSelected() const { return _thema_selected; }

    /**
     * @brief
     *
     */
    Q_INVOKABLE void showMessage();

    /**
     * @brief
     *
     * @return QString
     */
    Q_INVOKABLE QString versionString() {return _version_string;}

    /**
     * @brief
     *
     * @return ImageProvider_C
     */
    ImageProvider_C* GetImageProvider() { return _image_provider; }

public:
    /**
     * @brief
     *
     * @return ThemaModel_C
     */
    ThemaModel_C* GetThemaModel() {return _thema_model; }

    /**
     * @brief
     *
     * @return Settings_C
     */
    Settings_C* GetSettings() const { return _settings; }

    /**
     * @brief
     *
     * @param page_id
     * @param item
     */
    Q_INVOKABLE void setPageItem(PageId_TP page_id, QQuickItem* item);
    /**
     * @brief
     *
     * @param page_id
     * @return QQuickItem
     */
    QQuickItem* pageItem(PageId_TP page_id);

    /**
     * @brief
     *
     * @param page_id
     * @param item
     */
    Q_INVOKABLE void setPanelItem(PageId_TP page_id, QQuickItem* item);
    /**
     * @brief
     *
     * @param page_id
     * @return QQuickItem
     */
    QQuickItem* panelItem(PageId_TP page_id);

    /**
     * @brief
     *
     * @param page_id
     * @param item
     */
    Q_INVOKABLE void setTitleItem(PageId_TP page_id, QQuickItem* item);
    /**
     * @brief
     *
     * @param page_id
     * @return QQuickItem
     */
    QQuickItem* titleItem(PageId_TP page_id);

    /**
     * @brief
     *
     */
    Q_INVOKABLE void quit();

signals:
    /**
     * @brief
     *
     * @param old_page
     * @param new_page
     */
    void currentPageChanged(PageId_TP old_page, PageId_TP new_page);
    /**
     * @brief
     *
     */
    void gameLevelChanged();
    /**
     * @brief
     *
     */
    void themaSelectionStateChanged();
    
private slots:
    /**
     * @brief
     *
     * @param new_thema
     */
    void OnNewThemaLoaded(Thema_C* new_thema);
    /**
     * @brief
     *
     */
    void onThemaSelectionChanged();

// Helper methods
private:
    /**
     * @brief
     *
     */
    void LoadDefaultThemas();
    /**
     * @brief
     *
     */
    void InitPages();

private:
    Settings_C* _settings; /**< TODO */
    QQmlContext& _root_context; /**< TODO */
    QQuickItem* _root_item; /**< TODO */
    QHash<PageId_TP, PageItems_TP> _page_items_hash; /**< TODO */
    QHash<PageId_TP, Page_I*> _page_hash; /**< TODO */
    PageId_TP _current_page; /**< TODO */
    Result_C* _current_result; /**< TODO */
    ThemaModel_C* _thema_model; /**< TODO */
    GameLevel _game_level; /**< TODO */
    bool _thema_selected; /**< TODO */
    QString _version_string; /**< TODO */
    ImageProvider_C* _image_provider; /**< TODO */
};

#endif // MANAGER_H
