#include "manager.h"
#include <QQuickItem>

Manager_C::Manager_C(QObject *parent) :
    QObject(parent),
    _root_item(0)
{
}

void Manager_C::AddWords()
{
    AddWord("Wohnung");
    AddWord("Hause");
    AddWord("Bleistift");
    AddWord("Kuli");
}

QObject *Manager_C::AddWord(QString text)
{
    Q_ASSERT(_root_item);

    QVariant returned_value;
    QMetaObject::invokeMethod(_root_item, "addWord",
            Q_RETURN_ARG(QVariant, returned_value),
            Q_ARG(QVariant, text));
    QObject* word_item = returned_value.value<QObject*>();
    return word_item;
}
