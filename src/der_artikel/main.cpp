#include <QApplication>
#include <QQmlContext>
#include <QtQml>

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

#ifdef ENABLE_THEMA_BUILDER
#include "thema_builder.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<QAbstractItemModel>();
    qmlRegisterUncreatableType<Manager_C>("com.vystosi.qmlcomponents", 1, 0, "Manager","");
    qmlRegisterUncreatableType<Result_C>("com.vystosi.qmlcomponents", 1, 0, "Result","");
    qmlRegisterUncreatableType<Article_C>("com.vystosi.qmlcomponents", 1, 0, "Article","");
    qmlRegisterUncreatableType<Thema_C>("com.vystosi.qmlcomponents", 1, 0, "Thema","");
    qmlRegisterUncreatableType<ThemaModel_C>("com.vystosi.qmlcomponents", 1, 0, "ThemaModel","");
    qmlRegisterUncreatableType<HelpPage_C>("com.vystosi.qmlcomponents", 1, 0, "HelpPage","");
    qmlRegisterUncreatableType<Settings_C>("com.vystosi.qmlcomponents", 1, 0, "Settings","");
    qmlRegisterUncreatableType<SettingsPage_C>("com.vystosi.qmlcomponents", 1, 0, "SettingsPage","");

    //qmlRegisterUncreatableType<WordsPage_C>("com.vystosi.qmlcomponents", 1, 0, "WordsPage","");

#ifdef ENABLE_THEMA_BUILDER
    ThemaBuilder_C thema_builder;
    thema_builder.show();
#endif

    QtQuick2ApplicationViewer viewer;

    QQmlContext* root_context = viewer.rootContext();
    Manager_C manager(*root_context);

    root_context->setContextProperty("manager", &manager);
    root_context->setContextProperty("currentResult", manager.GetCurrentResult());
    root_context->setContextProperty("themaModel", manager.GetThemaModel());
    root_context->setContextProperty("settings", manager.GetSettings());
    root_context->engine()->addImageProvider("rootImageProvider",manager.GetImageProvider());

    viewer.setSource(QUrl("qrc:/res/qml/der_artikel/main.qml"));

    QQuickItem* root_item = viewer.rootObject();
    manager.SetRootItem(root_item);

    viewer.showExpanded();

    return app.exec();
}
