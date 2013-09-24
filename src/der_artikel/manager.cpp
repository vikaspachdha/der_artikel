#include "manager.h"
#include <QQuickItem>

Manager_C::Manager_C(QObject *parent) :
    QObject(parent),
    _root_item(0)
{
}

void Manager_C::AddWords()
{
    Q_ASSERT(_root_item);

    QVariant returnedValue;
    QVariant wordText = "Kleider";
    QMetaObject::invokeMethod(_root_item, "addWord",
            Q_RETURN_ARG(QVariant, returnedValue),
            Q_ARG(QVariant, wordText));
}
