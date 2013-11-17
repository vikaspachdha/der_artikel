#include "manager.h"
#include <QQuickItem>

#include "data/thema.h"
#include "thema_loader.h"
#include "algo/strict_result_algo.h"
#include "data/result.h"


Manager_C::Manager_C(QObject *parent) :
    QObject(parent),
    _root_item(0),
    _current_thema(0),
    _selected_article(ARTIKEL::DER),
    _current_page(HOME_PAGE),
    _result_algo(0),
    _current_result(0)
{
    SetSelectedArticle(_selected_article);
    LoadDefaultThemas();

    _thema_model = new ThemaModel_C(_themas, this);

    _result_algo = new StrictResultAlgo_C;
    _current_result = new Result_C(this);

    connect(this,SIGNAL(selectedArticleChanged()), this, SLOT(OnSelectedArticleChanged()) );
}

Manager_C::~Manager_C()
{
    delete _current_result;
    foreach(Thema_C* thema, _themas) {
        delete thema;
    }
}

void Manager_C::SetSelectedArticle(uint article)
{
    _selected_article = (ARTIKEL::Artikel)article;
    switch (_selected_article) {
    case ARTIKEL::DER:
        _current_word_color = QColor("#5287B1");
        break;
    case ARTIKEL::DIE:
        _current_word_color = QColor("#E882DA");
        break;
    case ARTIKEL::DAS:
        _current_word_color = QColor("#FFFFFF");
        break;
    case ARTIKEL::NA:
        _current_word_color = QColor("#FEF574");
        break;
    default:
        break;
    }

    _current_word_color.setAlpha(70);
}

void Manager_C::setCurrentPage(Manager_C::PageType new_page)
{
    if(_current_page != new_page) {
        PageType old_page = _current_page;
        _current_page = new_page;
        emit currentPageChanged(old_page,new_page);
    }
}


void Manager_C::OnNewThemaLoaded(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    Q_ASSERT(_thema_model);
    new_thema->setParent(this);
    _thema_model->AddThema(new_thema);
    //_themas.append(new_thema);
    SetCurrentThema(new_thema);
}

void Manager_C::OnSelectedArticleChanged()
{

}

void Manager_C::OnWordClicked()
{
    QObject* word_item = sender();
    Q_ASSERT(word_item);
    Word_C* word = _item_word_hash[word_item];
    if(word) {
        word->SetUserArtikel(_selected_article);
    }
}

void Manager_C::calculateResult()
{
    Q_ASSERT(_current_result);
    if(_current_thema) {
        _result_algo->Calculate(*_current_thema,*_current_result);
    }
}

void Manager_C::AddWords(const Thema_C* thema)
{
    foreach(Word_C* word, thema->GetWords()) {
        QObject* word_item = AddWord(word->GetWordText());
        Q_ASSERT(word_item);
        _item_word_hash[word_item] = word;
        connect(word_item, SIGNAL(wordClicked()), this, SLOT(OnWordClicked()) );
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
        ClearWordItems();
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

void Manager_C::ClearWordItems()
{
    foreach(QObject* word_item, _item_word_hash.keys()) {
        delete word_item;
    }
}

