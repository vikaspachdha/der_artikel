#include "manager.h"
#include <QQuickItem>

#include "data/thema.h"
#include "thema_loader.h"

Manager_C::Manager_C(QObject *parent) :
    QObject(parent),
    _root_item(0),
    _current_thema(0)
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
    Q_ASSERT(new_thema);
    new_thema->setParent(this);
    _themas.append(new_thema);
    SetCurrentThema(new_thema);
}

void Manager_C::AddWords(const Thema_C* thema)
{
    foreach(Word_C* word, thema->GetWords()) {
        AddWord(word->GetWordText());
    }
}

void Manager_C::LoadDefaultThemas()
{
    ThemaLoader_C* thema_loader = new ThemaLoader_C(this);
    connect(thema_loader, SIGNAL(ThemaLoaded(Thema_C*)), this, SLOT(OnNewThemaLoaded(Thema_C*)) );
    thema_loader->StartLoading();
}

void Manager_C::SetCurrentThema(Thema_C *thema)
{
    if(thema && thema != _current_thema) {
        _current_thema = thema;
        AddWords(_current_thema);
    }
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
