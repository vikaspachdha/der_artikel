#include "words_page.h"

#include <QQuickItem>
#include <QQmlContext>

#include "algo/result_algo.h"
#include "thema_model.h"

WordsPage_C::WordsPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent):
    Page_C(Manager_C::WORDS_PAGE,page_manager, parent),
    _root_context(root_context),
    _info_mode(false),
    _selected_article(Article_C::INVALID)
{
    _root_context.setContextProperty("words_page",this);
    SetSelectedArticle(Article_C::DER);
}

void WordsPage_C::enter()
{
    Thema_C* thema = _page_manager.GetThemaModel()->GetSelectedThema();
    Q_ASSERT(thema);
    AddWords(thema);

    ResultAlgo_I* algo = _page_manager.resultAlgo();
    if(algo) {
        int play_time = algo->playTime(*thema);
        QQuickItem* title_item = _page_manager.titleItem(_page_id);
        if(title_item) {
            title_item->setProperty("play_time",play_time);
            title_item->setProperty("timer_running",true);
        }
    }
}

void WordsPage_C::leave()
{
    ClearWordItems();

    Thema_C* thema = _page_manager.GetThemaModel()->GetSelectedThema();
    Q_ASSERT(thema);
    thema->ClearUserInput();

    QQuickItem* title_item = _page_manager.titleItem(_page_id);
    if(title_item) {
        title_item->setProperty("timer_running",false);
    }
}

void WordsPage_C::setInfoMode(bool info_mode)
{
    if(_info_mode != info_mode) {
        _info_mode = info_mode;
        emit infoModeChanged();
    }
}

void WordsPage_C::SetSelectedArticle(Article_C::Artikel article)
{
    if(_selected_article != article) {
        _selected_article = article;
        switch (_selected_article) {
        case Article_C::DER:
            _current_word_color = QColor("#5287B1");
            break;
        case Article_C::DIE:
            _current_word_color = QColor("#E882DA");
            break;
        case Article_C::DAS:
            _current_word_color = QColor("#FFFFFF");
            break;
        case Article_C::NA:
            _current_word_color = QColor("#FEF574");
            break;
        default:
            break;
        }

        _current_word_color.setAlpha(70);
        emit selectedArticleChanged();
    }
}

void WordsPage_C::OnWordClicked()
{
    QObject* word_item = sender();
    Q_ASSERT(word_item);
    Word_C* word = _item_word_hash[word_item];
    if(word) {
        word->SetUserArtikel(_selected_article);
    }
}

void WordsPage_C::AddWords(const Thema_C* thema)
{
    foreach(Word_C* word, thema->GetWords()) {
        QObject* word_item = AddWord(word->GetWordText(), word->GetDescription());
        Q_ASSERT(word_item);
        _item_word_hash[word_item] = word;
        connect(word_item, SIGNAL(wordClicked()), this, SLOT(OnWordClicked()) );
    }
}

QObject *WordsPage_C::AddWord(QString text, QString desc)
{
    QVariant returned_value;
    QMetaObject::invokeMethod(pageItem(), "addWord",
                              Q_RETURN_ARG(QVariant, returned_value),
                              Q_ARG(QVariant, text), Q_ARG(QVariant, desc));
    QObject* word_item = returned_value.value<QObject*>();
    return word_item;
}

void WordsPage_C::ClearWordItems()
{
    foreach(QObject* word_item, _item_word_hash.keys()) {
        delete word_item;
    }
    _item_word_hash.clear();
}



