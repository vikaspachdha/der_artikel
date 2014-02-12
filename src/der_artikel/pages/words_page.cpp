#include "words_page.h"

#include <QQuickItem>
#include <QQmlContext>

#include "algo/result_algo.h"
#include "algo/easy_result_algo.h"
#include "algo/moderate_result_algo.h"
#include "algo/strict_result_algo.h"
#include "thema_model.h"

/*!
 \brief

 \param page_manager
 \param root_context
 \param parent
*/
WordsPage_C::WordsPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent):
    Page_C(Manager_C::WORDS_PAGE,page_manager, parent),
    _root_context(root_context),
    _info_mode(false),
    _selected_article(Article_C::INVALID),
    _result_algo(0)
{
    _root_context.setContextProperty("words_page",this);
    SetSelectedArticle(Article_C::DER);
}

/*!
 \brief

 \param prev_page_id
*/
void WordsPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    Thema_C* thema = _page_manager.GetThemaModel()->GetSelectedThema();
    Q_ASSERT(thema);
    if(_page_manager.gameLevel() == Manager_C::PRACTICE) {
        // Add words to page.
        AddWords(thema,true);
        setInfoMode(true);
    } else {
        setInfoMode(false);
        CreateResultAlgo();
        Q_ASSERT(_result_algo);

        // Calculate play time
        int play_time = _result_algo->playTime(*thema);
        QQuickItem* title_item = _page_manager.titleItem(_page_id);
        if(title_item) {
            title_item->setProperty("play_time",play_time);
            title_item->setProperty("timer_running",true);
        }

        // Add words to page.
        AddWords(thema);
    }
}

/*!
 \brief

 \param next_page_id
*/
void WordsPage_C::leave(Manager_C::PageId_TP next_page_id)
{
    if(next_page_id==Manager_C::RESULT_PAGE) {
        CalculateResult();
    }
    ClearWordItems();

    Thema_C* thema = _page_manager.GetThemaModel()->GetSelectedThema();
    Q_ASSERT(thema);
    thema->ClearUserInput();

    QQuickItem* title_item = _page_manager.titleItem(_page_id);
    if(title_item) {
        title_item->setProperty("timer_running",false);
    }
}

/*!
 \brief

 \param info_mode
*/
void WordsPage_C::setInfoMode(bool info_mode)
{
    if(_info_mode != info_mode) {
        _info_mode = info_mode;
        if(_info_mode) {
            SetSelectedArticle(Article_C::NA);
        }
        emit infoModeChanged();
    }
}

/*!
 \brief

 \param article
*/
void WordsPage_C::SetSelectedArticle(Article_C::Artikel article)
{
    if(_selected_article != article) {
        _selected_article = article;
        if(_selected_article != Article_C::NA) {
            setInfoMode(false);
        }
        emit selectedArticleChanged();
    }
}

/*!
 \brief

*/
void WordsPage_C::OnWordClicked()
{
    QObject* word_item = sender();
    Q_ASSERT(word_item);
    Word_C* word = _item_word_hash[word_item];
    if(word) {
        word->SetUserArtikel(_selected_article);
    }
}

/*!
 \brief

 \param thema
 \param practice_mode
*/
void WordsPage_C::AddWords(const Thema_C* thema, bool practice_mode)
{
    QList<Word_C*> words = thema->GetWords();
    srand(QDateTime::currentMSecsSinceEpoch());
    while (words.count() > 0) {
        int index = rand()%words.count();
        Word_C* word = words.takeAt(index);
        if(practice_mode) {
            word->SetUserArtikel(word->GetArtikel());
        }
        QObject* word_item = AddWord(*word);
        Q_ASSERT(word_item);
        _item_word_hash[word_item] = word;
        connect(word_item, SIGNAL(wordClicked()), this, SLOT(OnWordClicked()) );
    }
}

/*!
 \brief

 \param word
 \return QObject
*/
QObject *WordsPage_C::AddWord(Word_C& word)
{
    QVariant returned_value;
    QMetaObject::invokeMethod(pageItem(), "addWord",
                              Q_RETURN_ARG(QVariant, returned_value),
                              Q_ARG(QVariant, QVariant::fromValue<QObject*>(&word)),
                              Q_ARG(QVariant, word.GetWordText()),
                              Q_ARG(QVariant, word.GetDescription()));
    QObject* word_item = returned_value.value<QObject*>();
    return word_item;
}

/*!
 \brief

*/
void WordsPage_C::ClearWordItems()
{
    foreach(QObject* word_item, _item_word_hash.keys()) {
        delete word_item;
    }
    _item_word_hash.clear();
}

/*!
 \brief

*/
void WordsPage_C::CreateResultAlgo()
{
    if(_result_algo) {
        delete _result_algo;
        _result_algo = 0;
    }
    switch (_page_manager.gameLevel()) {
        case Manager_C::EASY:
            _result_algo = new EasyResultAlgo_C();
            break;
        case Manager_C::MODERATE:
            _result_algo = new ModerateResultAlgo_C();
            break;
        case Manager_C::EXPERT:
            _result_algo = new StrictResultAlgo_C();
            break;
        default:
            break;
    }
}

/*!
 \brief

*/
void WordsPage_C::CalculateResult()
{
    Thema_C* current_thema = _page_manager.GetThemaModel()->GetSelectedThema();
    if(current_thema) {
        _result_algo->Calculate(*current_thema,*(_page_manager.GetCurrentResult()));
        current_thema->setLastPlayed(QDateTime::currentDateTimeUtc());
        current_thema->Save();
    }
}



