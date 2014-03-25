#include <QApplication>
#include <QQmlContext>
#include <QtQml>
#include <iostream>

#include "log4qt/ttcclayout.h"
#include "log4qt/logmanager.h"
#include "log4qt/fileappender.h"
#include "log4qt/logger.h"
#include "log_defines.h"

#include "qtquick2applicationviewer.h"
#include "manager.h"
#include "image_provider.h"
#include "data/result.h"
#include "data/thema.h"
#include "thema_model.h"
#include "settings.h"
#include "pages/help_page.h"
#include "pages/words_page.h"
#include "pages/settings_page.h"
#include "common.h"
#include "thema_updater.h"
#include "version.h"

#ifdef ENABLE_THEMA_BUILDER
#include "thema_builder.h"
#endif


void setupVersion()
{
    // Calculate version string.
    int version = APP_VERSION;
    QString version_string;
    while(version >= 10) {
        version_string.prepend("."+QString::number(version%10));
        version /= 10;
    }
    version_string.prepend(QString::number(version));
    qApp->setApplicationVersion(version_string);
}

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
    Log4Qt::LogManager::setThreshold(Log4Qt::Level::ALL_INT);
#else
    Log4Qt::LogManager::setThreshold(Log4Qt::Level::INFO_INT);
#endif
}

/*!
 \brief

 \param argc
 \param argv[]
 \return int
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    setupVersion();

    // Setup log files.
    setUpLogging();
    LOG_INFO("Application start")

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

#ifdef ENABLE_THEMA_BUILDER
    ThemaBuilder_C thema_builder;
    thema_builder.show();
#endif

    QtQuick2ApplicationViewer viewer;
    app.setWindowIcon(QIcon("qrc:/res/resources/app.png"));

    QQmlContext* root_context = viewer.rootContext();
    Manager_C manager(*root_context);
    ThemaUpdater_C thema_updater(manager);

    root_context->setContextProperty("manager", &manager);
    root_context->setContextProperty("themaUpdater", &thema_updater);
    root_context->setContextProperty("currentResult", manager.GetCurrentResult());
    root_context->setContextProperty("themaModel", manager.GetThemaModel());
    root_context->setContextProperty("settings", manager.GetSettings());
    root_context->engine()->addImageProvider("rootImageProvider",manager.GetImageProvider());

    viewer.setSource(QUrl("qrc:/res/qml/der_artikel/main.qml"));

    QQuickItem* root_item = viewer.rootObject();
    manager.SetRootItem(root_item);

    viewer.setMinimumSize(QSize(480,400));
    viewer.showExpanded();

    int return_code = app.exec();
    LOG_INFO("Application end")
    return return_code;
}
