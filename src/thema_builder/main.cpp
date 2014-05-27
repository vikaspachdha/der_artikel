#include <QApplication>
#include <QThread>
#include <QIcon>

#include "log4qt/ttcclayout.h"
#include "log4qt/logmanager.h"
#include "log4qt/fileappender.h"
#include "log4qt/logger.h"
#include "log4qt/log_defines.h"

#include "data/version.h"
#include "data/result.h"
#include "data/thema.h"

#include "thema_builder.h"

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
    p_layout->setHeader("thema_builder log file : Version : " + qApp->applicationVersion());

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
    app.thread()->setObjectName("mainThread");
    setupVersion();
    // Setup log files.
    setUpLogging();
    LOG_INFO("Application start");

    app.setWindowIcon(QIcon("qrc:/res/resources/app.png"));
    QApplication::setOrganizationName("vystosi");
    QApplication::setOrganizationDomain("vystosi.com");
    QApplication::setApplicationName("thema_builder");
    QApplication::setApplicationDisplayName("Thema builder");

    ThemaBuilder_C thema_builder;
    thema_builder.show();

    int return_code = app.exec();
    LOG_INFO("Application end");
    return return_code;
}
