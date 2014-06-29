//******************************************************************************
/*! \file thema_model.h Declaration of \ref ThemaModel_C
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
#ifndef THEMA_MODEL_H
#define THEMA_MODEL_H

// System includes
#include <QAbstractListModel>
#include <QList>

// Project includes
#include "data/thema.h"


//******************************************************************************
/*! \brief Model class for ref Thema_C "thema" objects.
 *
 *  \details Keeps the selection state and word count.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class ThemaModel_C : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(SelectionState_TP)

    // Properties
    Q_PROPERTY(SelectionState_TP selection_state READ SelectionState NOTIFY themaSelectionChanged)
    Q_PROPERTY(Thema_C* selected_thema READ GetSelectedThema NOTIFY themaSelectionChanged)
    Q_PROPERTY(int total_word_count READ totalWordCount NOTIFY totalWordCountChanged)

// Data types
public:

    //! Selection state.
    //! <ul>
    //!     <li>NO_SELECTION - No thema is slected
    //!     <li>SINGLE_SELECTION - Single thema is selected.
    //!     <li>MULTIPLE_SELECTION - Multiple thema are selected.
    //! </ul>
    enum SelectionState_TP {
        NO_SELECTION = 1,
        SINGLE_SELECTION,
        MULTIPLE_SELECTION
    };

    //! Thema data roles.
    enum ROLES_TP {
        DISPLAY_NAME=Qt::UserRole+1,
        TR_NAME,
        AUTHOR,
        SELECTED,
        EXPERIENCE,
        WORD_COUNT,
        THEMA_STATE,
        LAST_PLAYED,
        LAST_UPDATED,
        THEMA_OBJECT
    };


public:
    explicit ThemaModel_C(QObject *parent = 0);
    ~ThemaModel_C();

// QAbstarctItemModel Implementation.
public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int,QByteArray> roleNames() const;

public:
    void AddThema(Thema_C* new_thema);
    void clear();
    Thema_C* GetSelectedThema();
    Q_INVOKABLE void clearSelection();
    SelectionState_TP SelectionState() const;
    //! Returns total number of words loaded into the system.
    int totalWordCount() const { return _total_word_count; }

signals:
    //! Emitted when thema selection is changed.
    void themaSelectionChanged();
    //! Emitted when total word count changes.
    void totalWordCountChanged();

private slots:
    void onThemaItemSelectionChanged();

private:
    void clearThemaList();

private:
    //! List of thema instances.
    QList<Thema_C*> _thema_list;
    //! List of thema objects selected.
    QList<Thema_C*> _selected_thema_list;
    //! Total number of words loaded.
    int _total_word_count;
};

#endif // THEMA_MODEL_H
