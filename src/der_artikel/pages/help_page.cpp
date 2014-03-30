#include "help_page.h"
#include <QQmlContext>
#include "log_defines.h"

/*!
 \brief

 \param page_manager
 \param root_context
 \param parent
*/
HelpPage_C::HelpPage_C(Manager_C& page_manager,QQmlContext &root_context, QObject *parent) :
    Page_C(Manager_C::HELP_PAGE, page_manager, parent),
    _root_context(root_context),
    _sub_page_type(GENERAL)
{
    _root_context.setContextProperty("help_page_instance",this);
}

/*!
 \brief

 \param prev_page_id
*/
void HelpPage_C::enter(Manager_C::PageId_TP prev_page_id)
{
    Q_UNUSED(prev_page_id)
    setSubPageType(GENERAL);
}

/*!
 \brief

 \return QString
*/
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

/*!
 \brief

 \return QString
*/
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

/*!
 \brief

 \param sub_page_type
*/
void HelpPage_C::setSubPageType(const SubPage_TP &sub_page_type)
{
    if(_sub_page_type != sub_page_type) {
        LOG_INFO(QString("Help page :: Settings sub page %1").arg(sub_page_type));
        _sub_page_type = sub_page_type;
        emit subPageChanged();
    }
}
