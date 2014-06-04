#include <QPixmap>
#include "thema_model.h"
#include "log4qt/log_defines.h"

/*!
 \brief

 \param parent
*/
ThemaModel_C::ThemaModel_C(QObject *parent):
    QAbstractListModel(parent)
{

}

/*!
 \brief

*/
ThemaModel_C::~ThemaModel_C()
{
    clearThemaList();
}

/*!
 \brief

 \param index
 \param role
 \return QVariant
*/
QVariant ThemaModel_C::data(const QModelIndex &index, int role) const
{
    QVariant data;

    if(index.isValid() && index.row() < _thema_list.count()) {
        Thema_C* thema = _thema_list.at(index.row());
        if(thema) {

            switch(role) {

            case DISPLAY_NAME:
                data = thema->name();
                break;

            case TR_NAME:
                data = thema->trName();
                break;

            case AUTHOR:
                data = thema->author();
                break;

            case SELECTED:
                data = thema->selected();
                break;

            case EXPERIENCE:
                data = thema->experiencePoints();
                break;

            case WORD_COUNT:
                data = thema->wordCount();
                break;

            case THEMA_STATE:
                data = thema->state();
                break;

            case LAST_PLAYED:
                data = thema->lastPlayed();
                break;

            case LAST_UPDATED:
                data = thema->lastUpdated();
                break;

            case THEMA_OBJECT:
                data = QVariant::fromValue<QObject*>(thema);
                break;
            default:
                break;
            }

        }
    }


    return data;
}

/*!
 \brief

 \param parent
 \return int
*/
int ThemaModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _thema_list.count();
}

/*!
 \brief

 \return QHash<int, QByteArray>
*/
QHash<int, QByteArray> ThemaModel_C::roleNames() const
{
    QHash<int,QByteArray> roleNames;
    roleNames[DISPLAY_NAME] = "display_name";
    roleNames[TR_NAME] = "tr_name";
    roleNames[AUTHOR] = "author";
    roleNames[SELECTED] = "selected";
    roleNames[EXPERIENCE] = "experience";
    roleNames[WORD_COUNT] = "word_count";
    roleNames[THEMA_STATE] = "thema_state";
    roleNames[LAST_PLAYED] = "last_played";
    roleNames[LAST_UPDATED] = "last_updated";
    roleNames[THEMA_OBJECT] = "thema_object";
    return roleNames;
}

/*!
 \brief

 \param new_thema
*/
void ThemaModel_C::AddThema(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    LOG_INFO(QString("Thema model :: Added new thema %1").arg(new_thema->name()));
    beginInsertRows(QModelIndex(),_thema_list.count(),_thema_list.count());
    _thema_list.append(new_thema);
    connect(new_thema, SIGNAL(selectionChanged()),this,SLOT(OnThemaItemSelectionChanged()));
    endInsertRows();
}

void ThemaModel_C::clear()
{
    LOG_INFO("Thema model :: Cleared thema model");
    clearSelection();
    beginResetModel();
    clearThemaList();
    endResetModel();
}

/*!
 \brief

 \return Thema_C
*/
Thema_C* ThemaModel_C::GetSelectedThema()
{
    Thema_C* thema = 0;
    if(_selected_thema_list.count() > 0 ) {
        thema = _selected_thema_list.at(0);
    }
    return thema;
}

/*!
 \brief

*/
void ThemaModel_C::clearSelection()
{
    LOG_INFO("Thema model :: Cleared selection.");
    foreach (Thema_C* thema, _selected_thema_list) {
       thema->setSelected(false);
    }
    _selected_thema_list.clear();
}

/*!
 \brief

 \return ThemaModel_C::SelectionState_TP
*/
ThemaModel_C::SelectionState_TP ThemaModel_C::SelectionState() const
{
    SelectionState_TP selection_state;

    switch (_selected_thema_list.count()) {
        case 0:
           selection_state = NO_SELECTION;
            break;
        case 1:
           selection_state = SINGLE_SELECTION;
            break;
        default:
            selection_state = MULTIPLE_SELECTION;
            break;
    }

    return selection_state;
}

/*!
 \brief

 \param type
*/
void ThemaModel_C::OnThemaItemSelectionChanged()
{
    Thema_C* thema = qobject_cast<Thema_C*>(sender());
    Q_ASSERT(thema);

    if(thema->selected()) {
        LOG_INFO(QString("Thema model :: Thema %1 added to selection list.").arg(thema->name()));
        _selected_thema_list.append(thema);
    } else {
        LOG_INFO(QString("Thema model :: Thema %1 removed from selection list.").arg(thema->name()));
        _selected_thema_list.removeAll(thema);
    }

    emit themaSelectionChanged();

    QModelIndex thema_index = index(_thema_list.indexOf(thema));
    QVector<int> roles;
    roles<<SELECTED;
    emit dataChanged(thema_index,thema_index,roles);
}

void ThemaModel_C::clearThemaList()
{
    LOG_INFO("Removing all themas");
    foreach(Thema_C* thema, _thema_list) {
        delete thema;
    }
    _thema_list.clear();
}
