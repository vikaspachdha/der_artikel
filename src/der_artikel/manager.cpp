#include "manager.h"
#include <QQuickItem>

#include "data/thema.h"
#include "thema_loader.h"

Manager_C::Manager_C(QObject *parent) :
    QObject(parent),
    _root_item(0)
{
    LoadDefaultThemas();
}

Manager_C::~Manager_C()
{
    foreach(Thema_C* thema, _themas) {
        delete thema;
    }
}

void Manager_C::OnNewThemaLoaded(Thema_C *new_thema)
{
    _themas.append(new_thema);
}

void Manager_C::AddWords()
{
    AddWord("Wohnung");
    AddWord("Hause");
    AddWord("Bleistift");
    AddWord("Kuli");
}

void Manager_C::LoadDefaultThemas()
{
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    connect(thema_loader, SIGNAL(ThemaLoaded(Thema_C*)), this, SLOT(OnNewThemaLoaded(Thema_C*)) );
    thema_loader->StartLoading();
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
