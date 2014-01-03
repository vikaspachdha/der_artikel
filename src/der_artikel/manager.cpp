#include "manager.h"
#include <QApplication>
#include <QQuickItem>
#include <QQmlContext>
#include <QMessageBox>
#include <QDebug>

#include "data/thema.h"
#include "thema_loader.h"
#include "settings.h"
#include "algo/easy_result_algo.h"
#include "algo/moderate_result_algo.h"
#include "algo/strict_result_algo.h"
#include "data/result.h"
#include "version.h"

#include "pages/help_page.h"
#include "pages/words_page.h"
#include "pages/stats_page.h"
#include "pages/settings_page.h"


Manager_C::Manager_C(QQmlContext& ref_root_context, QObject *parent) :
    QObject(parent),
    _settings(0),
    _root_context(ref_root_context),
    _root_item(0),
    _current_thema(0),
    _selected_article(Article_C::INVALID),
    _current_page(INVALID_PAGE),
    _result_algo(0),
    _current_result(0),
    _game_level(EASY),
    _thema_selected(false)
{
    int version = APP_VERSION;
    while(version >= 10) {
        _version_string.prepend("."+QString::number(version%10));
        version /= 10;
    }
    _version_string.prepend(QString::number(version));

    _settings = new Settings_C(this);

    InitPages();
    SetSelectedArticle(Article_C::DER);

    _thema_model = new ThemaModel_C(this);
    connect(_thema_model,SIGNAL(themaSelectionChanged()), this, SLOT(onThemaSelectionChanged()));

    LoadDefaultThemas();
    _current_result = new Result_C(this);
    connect(this,SIGNAL(selectedArticleChanged()), this, SLOT(OnSelectedArticleChanged()) );
}

Manager_C::~Manager_C()
{
    delete _current_result;
    delete _thema_model;
}

void Manager_C::SetSelectedArticle(Article_C::Artikel article)
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

void Manager_C::setCurrentPage(Manager_C::PageId_TP new_page)
{
    if(_current_page != new_page) {
        PageId_TP old_page = _current_page;

        bool continue_shift = true;
        Page_I* old_page_instance = _page_hash[old_page];
        Page_I* new_page_instance =_page_hash[new_page];

        if(old_page_instance && !old_page_instance->canLeave()) {
            continue_shift = false;
        }

        if(new_page_instance && !new_page_instance->canEnter()) {
            continue_shift = false;
        }

        if(continue_shift) {

            _current_page = new_page;

            switch(old_page){
                case RESULT_PAGE:
                    // from result to words page keep thema selection.
                    // replay case
                    if(_current_page != Manager_C::WORDS_PAGE) {
                        _thema_model->ClearSelection();
                    }
                    break;
                case WORDS_PAGE:
                    if(_current_page == Manager_C::RESULT_PAGE) {
                        CalculateResult();
                        ClearWordItems();
                    }
                default:
                    break;
            }

            switch(_current_page){
                case WORDS_PAGE:
                    // determine the thema
                    _current_thema = 0;
                    SetCurrentThema(_thema_model->GetSelectedThema());
                    CreateResultAlgo();
                    break;

                default:
                    break;
            }

            if(old_page_instance) {
                old_page_instance->leave();
            }

            if(new_page_instance) {
                new_page_instance->enter();
            }

            emit currentPageChanged(old_page,new_page);
        }
    }
}

void Manager_C::setGameLevel(Manager_C::GameLevel game_level)
{
    if(_game_level != game_level) {
        _game_level = game_level;
        emit gameLevelChanged();
    }
}

void Manager_C::showMessage()
{
    QVariant returnedVal;
    QMetaObject::invokeMethod(_root_item,"showMessage",Q_RETURN_ARG(QVariant,returnedVal));
}

void Manager_C::OnNewThemaLoaded(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    Q_ASSERT(_thema_model);
    new_thema->setParent(this);
    _thema_model->AddThema(new_thema);
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

void Manager_C::onThemaSelectionChanged()
{
    _thema_selected = _thema_model->GetSelectedThema() ? true : false;
    emit themaSelectionStateChanged();
}

void Manager_C::CalculateResult()
{
    Q_ASSERT(_current_result);
    if(_current_thema) {
        _result_algo->Calculate(*_current_thema,*_current_result);
        _current_thema->Save();
    }
}

void Manager_C::setPageItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._page_item = item;
    }
}

QQuickItem *Manager_C::pageItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._page_item;
    }
    return item;
}

void Manager_C::setPanelItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._panel_item = item;
    }
}

QQuickItem *Manager_C::panelItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = _page_items_hash[page_id]._panel_item;
    }
    return item;
}

void Manager_C::setTitleItem(Manager_C::PageId_TP page_id, QQuickItem *item)
{
    if(page_id != INVALID_PAGE && item) {
        _page_items_hash[page_id]._title_item = item;
    }
}

QQuickItem *Manager_C::titleItem(Manager_C::PageId_TP page_id)
{
    QQuickItem *item = 0;
    if(_page_items_hash.contains(page_id)) {
        item = item = _page_items_hash[page_id]._title_item;
    }
    return item;
}

void Manager_C::quit()
{
    QMessageBox::StandardButton res  =
            QMessageBox::information(0,tr("Quit"),
                                     tr("Do you realy want to quit"),
                                     QMessageBox::Yes,QMessageBox::No);
    if(res == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void Manager_C::AddWords(const Thema_C* thema)
{
    foreach(Word_C* word, thema->GetWords()) {
        QObject* word_item = AddWord(word->GetWordText(), word->GetDescription());
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
        _current_thema->ClearUserInput();
        AddWords(_current_thema);
    }
}

QObject *Manager_C::AddWord(QString text, QString desc)
{
    Q_ASSERT(_root_item);

    QVariant returned_value;
    QMetaObject::invokeMethod(_root_item, "addWord",
                              Q_RETURN_ARG(QVariant, returned_value),
                              Q_ARG(QVariant, text), Q_ARG(QVariant, desc));
    QObject* word_item = returned_value.value<QObject*>();
    return word_item;
}

void Manager_C::ClearWordItems()
{
    foreach(QObject* word_item, _item_word_hash.keys()) {
        delete word_item;
    }
    _item_word_hash.clear();
}

void Manager_C::CreateResultAlgo()
{
    if(_result_algo) {
        delete _result_algo;
        _result_algo = 0;
    }
    switch (_game_level) {
    case EASY:
        _result_algo = new EasyResultAlgo_C();
        break;
    case MODERATE:
        _result_algo = new ModerateResultAlgo_C();
        break;
    case EXPERT:
        _result_algo = new StrictResultAlgo_C();
        break;
    default:
        break;
    }
}

void Manager_C::InitPages()
{
    _page_hash[HELP_PAGE] = new HelpPage_C(*this, _root_context,this);
    _page_hash[WORDS_PAGE] = new WordsPage_C(*this, _root_context,this);
    _page_hash[STATS_PAGE] = new StatsPage_C(*this,_root_context,this);
    _page_hash[SETTINGS_PAGE] = new SettingsPage_C(*this,_root_context,this);
}

