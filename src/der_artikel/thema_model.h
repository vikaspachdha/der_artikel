#ifndef THEMA_MODEL_H
#define THEMA_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "data/thema.h"

class ThemaModel_C : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(SelectionState_TP)

    // Properties
    Q_PROPERTY(SelectionState_TP selection_state READ SelectionState NOTIFY themaSelectionChanged)
    Q_PROPERTY(Thema_C* selected_thema READ GetSelectedThema NOTIFY themaSelectionChanged)

// Data types
public:

    enum SelectionState_TP {
        NO_SELECTION = 1,
        SINGLE_SELECTION,
        MULTIPLE_SELECTION
    };


private:

    enum ROLES_TP {
        DISPLAY_NAME=Qt::UserRole+1,
        TR_NAME,
        ICON,
        SELECTED,
        PROGRESS,
        WORD_COUNT,
        THEMA_OBJECT
    };


public:
    explicit ThemaModel_C(QObject *parent = 0);
    ~ThemaModel_C();

// QAbstarctItemModel Implementation.
public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int,QByteArray> roleNames() const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

public:
    void AddThema(Thema_C* new_thema);
    Thema_C* GetSelectedThema();
    void ClearSelection();
    SelectionState_TP SelectionState() const;

signals:
    void themaSelectionChanged();


private slots:
    void OnThemaItemSelectionChanged(Thema_C::SelectionType_TP type);


private:
    QList<Thema_C*> _thema_list;
    QList<Thema_C*> _selected_thema_list;
};

#endif // THEMA_MODEL_H
