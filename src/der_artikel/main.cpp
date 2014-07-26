//******************************************************************************
/*! \file main.cpp Application entry point
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
#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <QtQml>
#include <iostream>

// Framework and lib includes
#include "log4qt/consoleappender.h"
#include "log4qt/fileappender.h"
#include "log4qt/log_defines.h"
#include "log4qt/logger.h"
#include "log4qt/logmanager.h"
#include "log4qt/ttcclayout.h"

// Project includes
#include "data/common.h"
#include "data/result.h"
#include "data/thema.h"
#include "data/version.h"
#include "image_provider.h"
#include "manager.h"
#include "message_bar.h"
#include "pages/help_page.h"
#include "pages/settings_page.h"
#include "pages/words_page.h"
#include "settings.h"
#include "thema_updater.h"
#include "app_updater.h"

// Framework and lib includes
#include "data/thema_model.h"


//******************************************************************************
/*! \brief Application version setup.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void setupVersion()
{
    // Calculate version string.
    int version = APP_VERSION;
    QString version_string_num = QString("%1").arg(version,3,10,QChar('0'));
    QString version_string;
    int index = 0;
    do {
        version_string.append(version_string_num[index++] + ".");
    }while(index < version_string_num.size());
    version_string = version_string.left(version_string.size()-1);
    qApp->setApplicationVersion(version_string);
    qApp->setOrganizationName("vystosi");
    qApp->setOrganizationDomain("vystosi.com");
    qApp->setApplicationName("der_artikel");
}


//******************************************************************************
/*! \brief Logging objects and file setup.
 *
 *  \details Logging level is set to ALL for debug mode.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent instance for logging objects.
 ******************************************************************************/
void setUpLogging(QObject* parent=0)
{
    Log4Qt::LogManager::rootLogger();
    Log4Qt::TTCCLayout *p_layout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601,parent);
    p_layout->setCategoryPrefixing(false);
    p_layout->setThreadPrinting(true);
    p_layout->setHeader("der_artikel log file : Version : " + qApp->applicationVersion());

    p_layout->activateOptions();
    // Create an appender
    Log4Qt::FileAppender *p_appender = new Log4Qt::FileAppender(p_layout,"der_artikel.log",parent);
    p_appender->activateOptions();
    // Set appender on root logger
    Log4Qt::Logger::rootLogger()->addAppender(p_appender);

#ifdef QT_DEBUG
    Log4Qt::ConsoleAppender* console_appender = new Log4Qt::ConsoleAppender(p_layout,Log4Qt::ConsoleAppender::STDOUT_TARGET,parent);
    console_appender->activateOptions();
    Log4Qt::Logger::rootLogger()->addAppender(console_appender);
    Log4Qt::LogManager::setThreshold(Log4Qt::Level::ALL_INT);
#else
    Log4Qt::LogManager::setThreshold(Log4Qt::Level::INFO_INT);
#endif
}

//******************************************************************************
/*! \brief Main function. Application entry point
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] argc : Count of arguments.
 *  \param[in] argv : Argument values.
 *
 *  \return int : Application return code.
 ******************************************************************************/
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.thread()->setObjectName("mainThread");
    setupVersion();

    // Setup log files.
    setUpLogging();
    LOG_INFO("Application start");

    qmlRegisterType<QAbstractItemModel>();
    qmlRegisterUncreatableType<Manager_C>("com.vystosi.qmlcomponents", 1, 0, "Manager","");
    qmlRegisterUncreatableType<Result_C>("com.vystosi.qmlcomponents", 1, 0, "Result","");
    qmlRegisterUncreatableType<Article_C>("com.vystosi.qmlcomponents", 1, 0, "Article","");
    qmlRegisterUncreatableType<Thema_C>("com.vystosi.qmlcomponents", 1, 0, "Thema","");
    qmlRegisterUncreatableType<ThemaModel_C>("com.vystosi.qmlcomponents", 1, 0, "ThemaModel","");
    qmlRegisterUncreatableType<HelpPage_C>("com.vystosi.qmlcomponents", 1, 0, "HelpPage","");
    qmlRegisterUncreatableType<Settings_C>("com.vystosi.qmlcomponents", 1, 0, "Settings","");
    qmlRegisterUncreatableType<SettingsPage_C>("com.vystosi.qmlcomponents", 1, 0, "SettingsPage","");
    qmlRegisterUncreatableType<ThemaUpdater_C>("com.vystosi.qmlcomponents", 1, 0, "ThemaUpdater","");
    qmlRegisterUncreatableType<AppUpdater_C>("com.vystosi.qmlcomponents", 1, 0, "AppUpdater","");
    qmlRegisterUncreatableType<MessageBar_C>("com.vystosi.qmlcomponents", 1, 0, "MessageBar","");

    QQmlApplicationEngine appEngine;
    QQmlContext* root_context = appEngine.rootContext();
    //

    Manager_C manager(*root_context);
    ThemaUpdater_C thema_updater(manager);
    AppUpdater_C app_updater(manager);

    // Copy the stock thema files.
    if(manager.appSettings()->copyStockThema()) {
        thema_updater.checkUpdate(":/res/resources/stock_themas");
    }

    root_context->setContextProperty("manager", &manager);
    root_context->setContextProperty("themaUpdater", &thema_updater);
    root_context->setContextProperty("appUpdater", &app_updater);
    root_context->setContextProperty("currentResult", manager.currentResult());
    root_context->setContextProperty("themaModel", manager.themaModel());
    root_context->setContextProperty("settings", manager.appSettings());
    root_context->setContextProperty("messageBarInstance",&MessageBar_C::instance());
    root_context->engine()->addImageProvider("rootImageProvider",manager.imageProvider());

    QQmlComponent component(&appEngine,QUrl("qrc:/res/qml/der_artikel/main.qml"),&app);
    QObject* root_item = component.create();
    manager.SetRootItem(root_item);
    qDebug()<<component.errors();

    int return_code = app.exec();
    LOG_INFO("Application end");
    return return_code;
}
