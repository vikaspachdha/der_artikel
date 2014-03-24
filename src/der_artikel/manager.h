/****************************************************************************
**
** Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
** Contact: http://www.vikaspachdha.com
**
** This file is part of the application der_artikel.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>
#include <QHash>
#include <QEventLoop>
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

/*!
 * \brief Main manager class responsible for workflow and pivot for exposing data models to UI.
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

    enum MessageType {
        ERROR_MSG = 1,
        WARNING_MSG,
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
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

    void setCurrentPage(PageId_TP new_page);
    //! Returns the id of the current page visible.
    PageId_TP getCurrentPage() const { return _current_page; }

    //! Returns the current result instance. The instance stores the result data
    //! of the las game played and the instance is updated as soon as user finished a game.
    Result_C* GetCurrentResult() { return _current_result; }

    //! Returns the current game level selected.
    GameLevel gameLevel() const { return _game_level; }
    void setGameLevel(GameLevel game_level);

    //! True if a thema selection is available, false otherwise.
    bool isThemaSelected() const { return _thema_selected; }

    void showMessage(QString title, QString message, int duration, MessageType type = INFO_MSG);
    void closeMessage();

    //! Returns the version string.
    Q_INVOKABLE QString versionString();

    //! Returns the Image provider instance. Dynamic images are provided
    //! by this image provider e.g. Thema icons.
    ImageProvider_C* GetImageProvider() { return _image_provider; }

public:
    ThemaModel_C* GetThemaModel() {return _thema_model; }

    //! Returns the \ref Settings_C instance. All the serializable settings are maintained by the returned instance.
    Settings_C* GetSettings() const { return _settings; }

    Q_INVOKABLE void setPageItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* pageItem(PageId_TP page_id);

    Q_INVOKABLE void setPanelItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* panelItem(PageId_TP page_id);

    Q_INVOKABLE void setTitleItem(PageId_TP page_id, QQuickItem* item);
    QQuickItem* titleItem(PageId_TP page_id);

    Q_INVOKABLE void quit();

    void LoadDefaultThemas();

signals:
    //! Emitted when current page is changed. \param old_page The page that is removed
    //! \param new_page The page that is set as the new page.
    void currentPageChanged(PageId_TP old_page, PageId_TP new_page);

    //! Emitted when game level is changed by the user.
    void gameLevelChanged();

    //! Emitted when thema selection state is changed.
    void themaSelectionStateChanged();

private slots:
    void OnNewThemaLoaded(Thema_C* new_thema);
    void onThemaSelectionChanged();

private:
    void InitPages();

private:
    Settings_C* _settings;
    QQmlContext& _root_context;
    QQuickItem* _root_item;
    QHash<PageId_TP, PageItems_TP> _page_items_hash;
    QHash<PageId_TP, Page_I*> _page_hash;
    PageId_TP _current_page;
    Result_C* _current_result;
    ThemaModel_C* _thema_model;
    GameLevel _game_level;
    bool _thema_selected;
    ImageProvider_C* _image_provider;
    QEventLoop _message_loop;
};

#endif // MANAGER_H
