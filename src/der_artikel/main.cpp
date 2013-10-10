#include <QApplication>
#include <QQmlContext>

#include "qtquick2applicationviewer.h"
#include "manager.h"
#include "thema_builder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ThemaBuilder_C thema_builder;
    thema_builder.show();

    Manager_C manager;

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("manager", &manager);
    viewer.setMainQmlFile(QStringLiteral("qml/der_artikel/main.qml"));

    QQuickItem* root_item = viewer.rootObject();
    manager.SetRootItem(root_item);

    viewer.showExpanded();
    manager.AddWords();

    return app.exec();
}
