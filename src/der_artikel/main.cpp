#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include "qtquick2applicationviewer.h"
#include "manager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

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
