#include "words_page.h"

#include <QQuickItem>
#include <QQmlContext>

#include "algo/result_algo.h"
#include "thema_model.h"

WordsPage_C::WordsPage_C(Manager_C &page_manager, QQmlContext &root_context, QObject *parent):
    Page_C(Manager_C::WORDS_PAGE,page_manager, parent),
    _root_context(root_context),
    _info_mode(false)
{
    _root_context.setContextProperty("words_page",this);
}

void WordsPage_C::enter()
{
    ResultAlgo_I* algo = _page_manager.resultAlgo();
    if(algo) {
        Thema_C* thema = _page_manager.GetThemaModel()->GetSelectedThema();
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
