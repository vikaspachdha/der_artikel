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
#include <QApplication>
#include <QQuickItem>
#include <QQmlContext>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

// Interface for this file
#include "manager.h"

#include "data/thema.h"
#include "thema_loader.h"
#include "settings.h"

#include "data/result.h"
#include "version.h"
#include "image_provider.h"

#include "pages/help_page.h"
#include "pages/words_page.h"
#include "pages/stats_page.h"
#include "pages/settings_page.h"
#include "pages/thema_page.h"



/*!
 * \brief Construtor
 *
 * \param ref_root_context The root qml context.
 * \param parent Parent object instance
 */
Manager_C::Manager_C(QQmlContext& ref_root_context, QObject *parent) :
    QObject(parent),
    _settings(0),
    _root_context(ref_root_context),
    _root_item(0),
    _current_page(INVALID_PAGE),
    _current_result(0),
    _game_level(EASY),
    _thema_selected(false),
    _image_provider(new ImageProvider_C)
{
    int version = APP_VERSION;
    while(version >= 10) {
        _version_string.prepend("."+QString::number(version%10));
        version /= 10;
    }
    _version_string.prepend(QString::number(version));

    _settings = new Settings_C(this);

    InitPages();

    _thema_model = new ThemaModel_C(this);
    connect(_thema_model,SIGNAL(themaSelectionChanged()), this, SLOT(onThemaSelectionChanged()));

    LoadDefaultThemas();
}

/*!
 \brief Destructor

*/
Manager_C::~Manager_C()
{
    delete _current_result;
    delete _thema_model;
}

/*!
 * \brief Changes the current page displayed on the ui. Call this method to change the page.
 * The page will only be changed if the conditions are met for the last page to leave and
 * new page to enter.
 *
 * \param new_page The id of the new page to show.
 */
void Manager_C::setCurrentPage(Manager_C::PageId_TP new_page)
{
    if(_current_page != new_page) {
        PageId_TP old_page = _current_page;

        bool continue_shift = true;
        Page_I* old_page_instance = _page_hash[old_page];
        Page_I* new_page_instance =_page_hash[new_page];

        if(old_page_instance && !old_page_instance->canLeave()) {
            continue_shift = false;
        }

        if(new_page_instance && !new_page_instance->canEnter()) {
            continue_shift = false;
        }

        if(continue_shift) {

            _current_page = new_page;

            if(old_page_instance) {
                old_page_instance->leave(_current_page);
            }

            if(new_page_instance) {
                new_page_instance->enter(old_page);
            }

            emit currentPageChanged(old_page,new_page);
        }
    }
}

/*!
 * \brief Sets the game level.
 *
 * \param game_level The new game level.
 */
void Manager_C::setGameLevel(Manager_C::GameLevel game_level)
{
    if(_game_level != game_level) {
        _game_level = game_level;
        emit gameLevelChanged();
    }
}

/*!
 \brief

*/
void Manager_C::showMessage(QString title, QString message, int duration, MessageType type)
{
    Q_ASSERT(_settings);
    QMetaObject::invokeMethod(_root_item,"showMessage",Q_ARG(QVariant,title),Q_ARG(QVariant,message),Q_ARG(QVariant,duration),Q_ARG(QVariant,type));
    QTimer::singleShot(_settings->messageAnimTime() + 200,&_message_loop,SLOT(quit()));
    _message_loop.exec();
}

/*!
 \brief

*/
void Manager_C::closeMessage()
{
    Q_ASSERT(_settings);
    QMetaObject::invokeMethod(_root_item,"closeMessage");
    QTimer::singleShot(_settings->messageAnimTime(),&_message_loop,SLOT(quit()));
    _message_loop.exec();
}

/*!
 * \brief Called when a new thema is loaded. \todo Move it to Thema model.
 *
 * \param new_thema
 */
void Manager_C::OnNewThemaLoaded(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    Q_ASSERT(_thema_model);
    new_thema->setParent(this);
    _thema_model->AddThema(new_thema);
    _image_provider->AddImage(new_thema->GetText(),new_thema->GetIcon());
}

/*!
 \brief Called when thema selection is changed

*/
void Manager_C::onThemaSelectionChanged()
{
    _thema_selected = _thema_model->GetSelectedThema() ? true : false;
    emit themaSelectionStateChanged();
}

/*!
 * \brief This method is called by the qml to set the Page QML item for the correspoding page.
 *
 * \param page_id The id of the page to which the item belongs.
 * \param item The page item.
 */
void Manager_C::setPageItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._page_item = item;
    }
}

/*!
 * \brief Returns the page item of the page.
 *
 * \param page_id The id of the page.
 * \return QQuickItem The page item of the page.
 */
QQuickItem *Manager_C::pageItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._page_item;
    }
    return item;
}

/*!
 * \brief This method is called by the qml to set the Panel QML item for the correspoding page.
 *
 * \param page_id The id of the page to which the item belongs.
 * \param item The panel item of the page.
 */
void Manager_C::setPanelItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._panel_item = item;
    }
}

/*!
 * \brief Returns the panel item of the page.
 *
 * \param page_id The id of the page.
 * \return QQuickItem The panel item of the page.
 */
QQuickItem *Manager_C::panelItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._panel_item;
    }
    return item;
}

/*!
 \brief This method is called by the qml to set the title QML item for the correspoding page.

 \param page_id The id of the page to which the item belongs.
 \param item The panel item of the page.
*/
void Manager_C::setTitleItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._title_item = item;
    }
}

/*!
 * \brief Returns the title item of the page.
 *
 * \param page_id The id of the page.
 * \return QQuickItem The title item of the page.
 */
QQuickItem *Manager_C::titleItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._title_item;
    }
    return item;
}

/*!
 * \brief Quits the application
 *
 */
void Manager_C::quit()
{
    QMessageBox::StandardButton res  =
            QMessageBox::information(0,tr("Quit"),
                                     tr("Do you realy want to quit"),
                                     QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes) {
        QApplication::quit();
    }
}

/*!
 \brief Start loading the default thema's. The thema present in the system.
*/
void Manager_C::LoadDefaultThemas()
{
    _current_result = new Result_C(this);
    if(_thema_model) {
        _thema_model->clear();
    }

    // thema_loader shall be deleted automatically.
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    connect(thema_loader, SIGNAL(ThemaLoaded(Thema_C*)), this, SLOT(OnNewThemaLoaded(Thema_C*)) );
    thema_loader->StartLoading();
}

/*!
 \brief Initializes the Pages. Dependencies are injected.
*
*/
void Manager_C::InitPages()
{
    _page_hash[HELP_PAGE] = new HelpPage_C(*this, _root_context,this);
    _page_hash[WORDS_PAGE] = new WordsPage_C(*this, _root_context,this);
    _page_hash[STATS_PAGE] = new StatsPage_C(*this,_root_context,this);
    _page_hash[SETTINGS_PAGE] = new SettingsPage_C(*this,_root_context,this);
    _page_hash[THEMA_PAGE] = new ThemaPage_C(*this,this);
}

