//******************************************************************************
/*! \file manager.h Declaration of \ref Manager_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
#ifndef MANAGER_H
#define MANAGER_H

// System includes
#include <QEventLoop>
#include <QHash>
#include <QObject>
#include <QVector>

// Framework & Lib includes
#include "data/article.h"

// Forward declarations
class AppUpdater_C;
class ImageProvider_C;
class Page_I;
class QQmlContext;
class QQuickItem;
class Result_C;
class ResultAlgo_I;
class Settings_C;
class Thema_C;
class ThemaModel_C;
class ThemaUpdater_C;
class Word_C;


//******************************************************************************
/*! \brief Main manager class responsible for workflow and pivot for exposing
 *  data models to UI.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class Manager_C : public QObject
{
    Q_OBJECT

    Q_ENUMS(PageId_TP)
    Q_ENUMS(GameLevel)

    Q_PROPERTY(PageId_TP current_page READ currentPage WRITE setCurrentPage NOTIFY currentPageChanged)
    Q_PROPERTY(ThemaModel_C* thema_model READ themaModel CONSTANT)
    Q_PROPERTY(GameLevel game_level READ gameLevel WRITE setGameLevel NOTIFY gameLevelChanged)
    Q_PROPERTY(bool thema_selected READ isThemaSelected NOTIFY themaSelectionStateChanged)
    Q_PROPERTY(QString version_string READ versionString CONSTANT)
    Q_PROPERTY(bool is_starting_up READ isStartingUp NOTIFY startupFinished)
public:

    //! Pages id's. Every page has an unique id.
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

    //! Game levels. A user can choose between these levels to play game.
    //! Different levels define different scoring and time to play the game.
    enum GameLevel {
        EASY=1,
        MODERATE,
        EXPERT,
        PRACTICE
    };

    //! Message types.
    enum MessageType {
        WARNING_MSG = 1,
        ERROR_MSG,
        INFO_MSG
    };

private:
    //! Each page has a panel item for hosting commands and a main display
    //! item called page item and a title item to show extra information.
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
    //! Sets the root qml Item. i.e the main item.
    void SetRootItem(QObject* root_Item);

    void setCurrentPage(PageId_TP new_page);
    //! Returns the id of the current page visible.
    PageId_TP currentPage() const { return _current_page; }

    //! Returns the current result instance. The instance stores the result data
    //! of the las game played and the instance is updated as soon as user finished a game.
    Result_C* currentResult() { return _current_result; }

    //! Returns the current game level selected.
    GameLevel gameLevel() const { return _game_level; }
    void setGameLevel(GameLevel game_level);

    //! Returns the Image provider instance. Dynamic images are provided
    //! by this image provider e.g. Thema icons.
    ImageProvider_C* imageProvider() { return _image_provider; }

    //! Returns thema model instance.
    ThemaModel_C* themaModel() {return _thema_model; }

    //! Returns thema updater instance.
    ThemaUpdater_C* themaUpdater() {return _thema_updater; }

    //! Returns app updater instance.
    AppUpdater_C* appUpdater() {return _app_updater; }

    //! Returns true if app is starting up, false otherwise.
    bool isStartingUp() const { return _starting_up; }

    bool isThemaSelected() const;

    //! Returns the version string.
    Q_INVOKABLE QString versionString();

    //! Returns the \ref Settings_C instance. All the serializable settings are maintained by the returned instance.
    Settings_C* appSettings() const { return _settings; }

    Q_INVOKABLE void setPageItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* pageItem(PageId_TP page_id);

    Q_INVOKABLE void setPanelItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* panelItem(PageId_TP page_id);

    Q_INVOKABLE void setTitleItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* titleItem(PageId_TP page_id);

    Q_INVOKABLE void onStartup();
    Q_INVOKABLE void onStartupCompleted();

    Q_INVOKABLE void quit();

    void loadDefaultThemas();

private slots:
    void onStockThemaUpdated();
    void onthemaFilesUpdated();
    void onNewthemaLoaded(Thema_C* new_thema);
    void onThemaLoadingProgress(double progress);
    void onThemaSelectionChanged();
    void quitPrivate();

signals:
    //! Emitted when current page is changed. \param old_page The page that is removed
    //! \param new_page The page that is set as the new page.
    void currentPageChanged(PageId_TP old_page, PageId_TP new_page);

    //! Emitted when game level is changed by the user.
    void gameLevelChanged();

    //! Emitted when thema selection state is changed.
    void themaSelectionStateChanged();

    void startupFinished();

private:
    void initPages();
    void finishStartup();

private:
    //! Application settings
    Settings_C* _settings;
    //! Root qml context to share data with QML.
    QQmlContext& _root_context;
    //! Root QML item.
    QObject* _root_item;
    //! Hash of \ref PageId_TP and page's QML items.
    QHash<PageId_TP, PageItems_TP> _page_items_hash;
    //! Hash of \ref PageId_TP and page's instance.
    QHash<PageId_TP, Page_I*> _page_hash;
    //! Current active page instance.
    PageId_TP _current_page;
    //! Last result from gameplay.
    Result_C* _current_result;
    //! Model of noun thema's
    ThemaModel_C* _thema_model;
    //! Game level selected.
    GameLevel _game_level;
    //! Application image provider
    ImageProvider_C* _image_provider;
    //! Stock thema updater instance.
    ThemaUpdater_C* _stock_thema_updater;
    //! Thema updater instance.
    ThemaUpdater_C* _thema_updater;
    //! App updater instance.
    AppUpdater_C* _app_updater;
    //!
    bool _starting_up;
};

#endif // MANAGER_H
