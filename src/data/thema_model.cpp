//******************************************************************************
/*! \file thema_model.cpp Implementation of \ref ThemaModel_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
// System includes
#include <QPixmap>

// Interface for this file
#include "thema_model.h"

// Framework and lib includes
#include "log4qt/log_defines.h"



//******************************************************************************
/*! \brief Constructor
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
ThemaModel_C::ThemaModel_C(QObject *parent):
    QAbstractListModel(parent),
    _total_word_count(0)
{

}

//******************************************************************************
/*! \brief Destructor
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
ThemaModel_C::~ThemaModel_C()
{
    clearThemaList();
}

//******************************************************************************
/*! \brief Returns the data stored under the given role for the item referred
 *  to by the index.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] index : Index of the item refered.
 *  \param[in] role : Role id to be accessed.
 *
 *  \return QVariant : Data associated with the role.
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Returns the number of rows under the given parent.
 *
 *  \details For this model it returns number of thema instances contained.
 *
 *  \author Vikas Pachdha
 *
 *  \return int : Number of thema instances managed by model.
 ******************************************************************************/
int ThemaModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _thema_list.count();
}

//******************************************************************************
/*! \brief Returns the model's role names.
 *
 *  \author Vikas Pachdha
 *
 *  \return QHash<int, QByteArray> : Hash of role id's and role names.
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Add a thema instance to the model. Ownership is maintained by the model.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] new_thema : Thema instance to be added.
 ******************************************************************************/
void ThemaModel_C::AddThema(Thema_C *new_thema)
{
    Q_ASSERT(new_thema);
    LOG_INFO(QString("Thema model :: Added new thema %1").arg(new_thema->name()));
    beginInsertRows(QModelIndex(),_thema_list.count(),_thema_list.count());
    _thema_list.append(new_thema);
    connect(new_thema, SIGNAL(selectionChanged()),this,SLOT(onThemaItemSelectionChanged()));
    endInsertRows();

    _total_word_count += new_thema->wordCount();
    emit totalWordCountChanged();
}

//******************************************************************************
/*! \brief Clears the model. All saved states and data is cleared
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaModel_C::clear()
{
    LOG_INFO("Thema model :: Cleared thema model");
    _total_word_count = 0;
    clearSelection();
    clearThemaList();
    emit totalWordCountChanged();
}

//******************************************************************************
/*! \brief Returns the selected thema.
 *
 *  \author Vikas Pachdha
 *
 *  \return Thema_C* : Selected thema.
 ******************************************************************************/
Thema_C* ThemaModel_C::GetSelectedThema()
{
    Thema_C* thema = 0;
    if(_selected_thema_list.count() > 0 ) {
        thema = _selected_thema_list.at(0);
    }
    return thema;
}

//******************************************************************************
/*! \brief clears the thema selection.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaModel_C::clearSelection()
{
    LOG_INFO("Thema model :: Cleared selection.");
    foreach (Thema_C* thema, _selected_thema_list) {
       thema->setSelected(false);
    }
    _selected_thema_list.clear();
}

//******************************************************************************
/*! \brief Returns the selection state.
 *
 *  \author Vikas Pachdha
 *
 *  \return ThemaModel_C::SelectionState_TP : The scurrent election state.
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Called when thema selection is changed.
 *
 *  \details Selected thema is added to selection list and selection list is cleared
 *  if a thema is deselected.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaModel_C::onThemaItemSelectionChanged()
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

//******************************************************************************
/*! \brief Deletes all the thema instances managed. Thema model is reset.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void ThemaModel_C::clearThemaList()
{
    beginResetModel();
    LOG_INFO("Removing all themas");
    foreach(Thema_C* thema, _thema_list) {
        delete thema;
    }
    _thema_list.clear();
    endResetModel();
}
