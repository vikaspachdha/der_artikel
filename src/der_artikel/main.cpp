#include <QApplication>
#include <QQmlContext>

#include "qtquick2applicationviewer.h"
#include "manager.h"

#ifdef ENABLE_THEMA_BUILDER
#include "thema_builder.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef ENABLE_THEMA_BUILDER
    ThemaBuilder_C thema_builder;
    thema_builder.show();
#endif

    Manager_C manager;

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("manager", &manager);
    viewer.setMainQmlFile(QStringLiteral("qml/der_artikel/main.qml"));

    QQuickItem* root_item = viewer.rootObject();
    manager.SetRootItem(root_item);

    viewer.showExpanded();

    return app.exec();
}
