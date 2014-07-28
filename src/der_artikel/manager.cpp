//******************************************************************************
/*! \file manager.cpp Implementation of \ref Manager_C
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
// System includes
#include <QDebug>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickItem>
#include <QTimer>
#include <QSound>
// Interface for this file
#include "manager.h"

// Framework and lib includes
#include "data/result.h"
#include "data/thema.h"
#include "data/thema_loader.h"
#include "data/thema_model.h"
#include "data/version.h"
#include "log4qt/log_defines.h"

// Project includes
#include "image_provider.h"
#include "message_bar.h"
#include "pages/about_page.h"
#include "pages/help_page.h"
#include "pages/settings_page.h"
#include "pages/stats_page.h"
#include "pages/thema_page.h"
#include "pages/words_page.h"
#include "settings.h"

//******************************************************************************
/*! \brief Construtor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] ref_root_context : The root qml context.
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
Manager_C::Manager_C(QQmlContext& ref_root_context, QObject *parent) :
    QObject(parent),
    _settings(0),
    _root_context(ref_root_context),
    _root_item(0),
    _current_page(INVALID_PAGE),
    _current_result(0),
    _thema_model(0),
    _game_level(EASY),
    _image_provider(new ImageProvider_C)
{    
    LOG_DEBUG("Manager_C::Construtor");
    _settings = new Settings_C(this);
    _current_result = new Result_C(this);

    _thema_model = new ThemaModel_C(this);
    connect(_thema_model,SIGNAL(themaSelectionChanged()), this, SLOT(onThemaSelectionChanged()));

    initPages();
}

//******************************************************************************
/*! \brief Destructor
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
Manager_C::~Manager_C()
{
    LOG_DEBUG("Manager_C::Destructor");
    delete _current_result;
    _current_result = 0;
    delete _thema_model;
    _thema_model = 0;
    delete _settings;
    _settings = 0;

    foreach(PageId_TP page_id, _page_hash.keys()) {
        Page_I* page = _page_hash[page_id];
        if(page) {
            delete page;
        }
    }
    _page_hash.clear();
    _page_items_hash.clear();
}

//******************************************************************************
/*! \brief Sets root QML item.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] root_Item The root QML item.
 ******************************************************************************/
void Manager_C::SetRootItem(QObject *root_Item)
{
    _root_item = root_Item;
    QVariant msg_bar_object;
    QQuickItem* msg_bar_item = 0;
    QMetaObject::invokeMethod(_root_item,"getMessageBar",Q_RETURN_ARG(QVariant,msg_bar_object));
    msg_bar_item = msg_bar_object.value<QQuickItem*>();
    MessageBar_C::instance().init(msg_bar_item,_settings);
}

//******************************************************************************
/*! \brief Changes the current page displayed on the ui. Call this method to change the page.
 *  The page will only be changed if the conditions are met for the last page to leave and
 *  new page to enter.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_page The id of the new page to show.
 ******************************************************************************/
void Manager_C::setCurrentPage(Manager_C::PageId_TP new_page)
{
    LOG_DEBUG(QString("Manager_C::setCurrentPage : %1").arg(new_page));
    if(_current_page != new_page) {
        PageId_TP old_page = _current_page;

        bool continue_shift = true;
        Page_I* old_page_instance = _page_hash[old_page];
        Page_I* new_page_instance =_page_hash[new_page];

        if(old_page_instance && !old_page_instance->canLeave()) {
            LOG_INFO(QString("Manager :: Can not leave page %1").arg(old_page));
            continue_shift = false;
        }

        if(continue_shift && new_page_instance && !new_page_instance->canEnter()) {
            LOG_INFO(QString("Manager :: Can not enter page %1").arg(new_page));
            continue_shift = false;
        }

        if(continue_shift) {

            _current_page = new_page;

            if(old_page_instance) {
                LOG_INFO(QString("Manager :: Leaving page %1").arg(old_page));
                old_page_instance->leave(_current_page);
                LOG_INFO(QString("Manager :: Left page %1").arg(old_page));
            }

            emit currentPageChanged(old_page,new_page);
            if(old_page != INVALID_PAGE) {
                QSound::play(":/res/resources/sounds/page_flip.wav");
            }

            if(new_page_instance) {
                LOG_INFO(QString("Manager :: Entering page %1").arg(new_page));
                new_page_instance->enter(old_page);
                LOG_INFO(QString("Manager :: Entered page %1").arg(new_page));
            }
        }
    }
}

//******************************************************************************
/*! \brief Sets the game level.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] game_level The new game level.
 ******************************************************************************/
void Manager_C::setGameLevel(Manager_C::GameLevel game_level)
{
    if(_game_level != game_level) {
        LOG_INFO(QString("Manager :: New game level set - %1").arg(game_level));
        _game_level = game_level;
        emit gameLevelChanged();
    }
}

//******************************************************************************
/*! \brief Returns selected state of thema.
 *
 *  \author Vikas Pachdha
 *
 *  \return bool : True if a thema selection is available, false otherwise.
 ******************************************************************************/
bool Manager_C::isThemaSelected() const
{
    return _thema_model->GetSelectedThema() ? true: false;
}

//******************************************************************************
/*! \brief Return the version string.
 *
 *  \author Vikas Pachdha
 *
 *  \return QString : Version string.
 ******************************************************************************/
QString Manager_C::versionString()
{
    return qApp->applicationVersion();
}

//******************************************************************************
/*! \brief Called when a new thema is loaded.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_thema : The new loaded thema.
 ******************************************************************************/
void Manager_C::onNewthemaLoaded(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    Q_ASSERT(_thema_model);
    LOG_INFO(QString("Manager :: Thema %1 loaded").arg(new_thema->name()));
    new_thema->setParent(this);
    _thema_model->AddThema(new_thema);
    Q_ASSERT(_image_provider);
    _image_provider->addImage(new_thema->name(),new_thema->themaIcon());
}

//******************************************************************************
/*! \brief Called to notify them loading progress. Message bar is updates accordingly.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] progress : Progress value.
 ******************************************************************************/
void Manager_C::onThemaLoadingProgress(double progress)
{
    MessageBar_C::setProgress(progress);
    MessageBar_C::setMessage(QString("%1 %").arg(qRound(progress * 100)));
}

//******************************************************************************
/*! \brief Called when thema selection is changed.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Manager_C::onThemaSelectionChanged()
{
    Q_ASSERT(_thema_model);
    Thema_C* selected_thema = _thema_model->GetSelectedThema();
    if(selected_thema) {
        LOG_INFO(QString("Manager :: Thema selection changed to %1").arg(selected_thema->name()));
    } else {
        LOG_INFO(QString("Manager :: Thema selection changed to none"));
    }
    emit themaSelectionStateChanged();
}

//******************************************************************************
/*! \brief This method is called by the qml to set the Page QML item for the
 *  correspoding page.
 *
 *  \details Detailed description
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_id : The id of the page to which the item belongs.
 *  \param[in] item : The page item.
 ******************************************************************************/
void Manager_C::setPageItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        LOG_DEBUG(QString("Setting QML page item for page %1").arg(page_id));
        _page_items_hash[page_id]._page_item = item;
    }
}

//******************************************************************************
/*! \brief Returns the page item of the page.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_id : The id of the page.
 *
 *  \return QQuickItem* : The page item of the page.
 ******************************************************************************/
QQuickItem *Manager_C::pageItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(page_id != INVALID_PAGE) {
        if(_page_items_hash.contains(page_id)) {
            item = _page_items_hash[page_id]._page_item;
        } else {
            LOG_WARN(QString("Qml page item not avaiable for Page Id %1").arg(page_id));
        }
    }
    return item;
}

//******************************************************************************
/*! \brief This method is called by the qml to set the Panel QML item for the
 *  correspoding page.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_id The id of the page to which the item belongs.
 *  \param[in] item The panel item of the page.
 ******************************************************************************/
void Manager_C::setPanelItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        LOG_DEBUG(QString("Setting QML panel item for page %1").arg(page_id));
        _page_items_hash[page_id]._panel_item = item;
    }
}

//******************************************************************************
/*! \brief Returns the panel item of the page.
 *
 *  \details Detailed description
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_id : The id of the page.
 *
 *  \return QQuickItem* : The panel item of the page.
 ******************************************************************************/
QQuickItem *Manager_C::panelItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(page_id != INVALID_PAGE) {
        if(_page_items_hash.contains(page_id)) {
            item = _page_items_hash[page_id]._panel_item;
        } else {
            LOG_WARN(QString("Qml panel item not avaiable for Page Id %1").arg(page_id));
        }
    }
    return item;
}

//******************************************************************************
/*! \brief This method is called by the qml to set the title QML item for the
 *  correspoding page.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] page_id : The id of the page to which the item belongs.
 *  \param[in] item : The panel item of the page.
 ******************************************************************************/
void Manager_C::setTitleItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        LOG_DEBUG(QString("Setting QML title item for page %1").arg(page_id));
        _page_items_hash[page_id]._title_item = item;
    }
}

//******************************************************************************
/*! \brief Returns the title item of the page.
 *
 *  \author Vikas Pachdha
 *
 * \param[in] page_id : The id of the page.
 *
 * \return QQuickItem* : The title item of the page.
 ******************************************************************************/
QQuickItem *Manager_C::titleItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(page_id != INVALID_PAGE ) {
        if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._title_item;
        } else {
            LOG_WARN(QString("Qml title item not avaiable for Page Id %1").arg(page_id));
        }
    }
    return item;
}

//******************************************************************************
/*! \brief Quits the application.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Manager_C::quit()
{
    // https://bugreports.qt-project.org/browse/QTBUG-38729
    QTimer::singleShot(0,this,SLOT(quitPrivate()));
}

//******************************************************************************
/*! \brief Slot to Quit application.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Manager_C::quitPrivate()
{
    LOG_INFO("Quitting Application");
    if( MessageBar_C::showMsg(tr("Do you realy want to quit?"),"") == MessageBar_C::ACCEPTED) {
        QGuiApplication::quit();
    }
}

//******************************************************************************
/*! \brief Start loading the default thema's. The thema present in the system.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Manager_C::loadDefaultThemas()
{
    LOG_INFO("Manager :: Loading Thema files");
    Q_ASSERT(_thema_model);
    _thema_model->clear();
    // thema_loader shall be deleted automatically.
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    thema_loader->setRootThemaDir(_settings->defaultThemaDirPath());
    connect(thema_loader, SIGNAL(themaLoaded(Thema_C*)), SLOT(onNewthemaLoaded(Thema_C*)) );
    connect(thema_loader,SIGNAL(finishedLoading()),&MessageBar_C::instance(),SLOT(closeMsg()));
    connect(thema_loader,SIGNAL(updateProgress(double)),SLOT(onThemaLoadingProgress(double)));
    MessageBar_C::showMsgAsync(tr("Loading installed themas."),"",2000);
    thema_loader->startLoading();
}

//******************************************************************************
/*! \brief Initializes the Pages. Dependencies are injected.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void Manager_C::initPages()
{
    LOG_DEBUG("Manager_C::InitPages()");
    _page_hash[HELP_PAGE] = new HelpPage_C(*this, _root_context,this);
    _page_hash[ABOUT_PAGE] = new AboutPage_C(*this, _root_context,this);
    _page_hash[WORDS_PAGE] = new WordsPage_C(*this, _root_context,*_settings,this);
    _page_hash[STATS_PAGE] = new StatsPage_C(*this,_root_context,this);
    _page_hash[SETTINGS_PAGE] = new SettingsPage_C(*this,_root_context,this);
    _page_hash[THEMA_PAGE] = new ThemaPage_C(*this,this);
}

