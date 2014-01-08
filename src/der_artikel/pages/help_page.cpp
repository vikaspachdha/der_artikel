#include "help_page.h"
#include <QQmlContext>

HelpPage_C::HelpPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::HELP_PAGE, page_manager, parent),
    _root_context(root_context),
    _sub_page_type(GENERAL)
{
    _root_context.setContextProperty("help_page_instance",this);
}

void HelpPage_C::enter()
{
    setSubPageType(GENERAL);
}

QString HelpPage_C::title() const
{
    QString title = "";
    switch(_sub_page_type) {
    case GENERAL:
        title = tr("General");
        break;
    case RULES:
        title = tr("Rules");
        break;
    case SCORING:
        title = tr("Scoring");
        break;
    case OTHERS:
        title = tr("Contact");
        break;
    default:
        break;
    }

    return title;
}

QString HelpPage_C::subPage() const
{
    QString title = "";
    switch(_sub_page_type) {
    case GENERAL:
        title = "General_help.qml";
        break;
    case RULES:
        title = "Rules_help.qml";
        break;
    case SCORING:
        title = "Scoring_help.qml";
        break;
    case OTHERS:
        title = "Others_help.qml";
        break;
    default:
        break;
    }

    return title;
}

void HelpPage_C::setSubPageType(const SubPage_TP &sub_page_type)
{
    if(_sub_page_type != sub_page_type) {
        _sub_page_type = sub_page_type;
        emit subPageChanged();
    }
}
