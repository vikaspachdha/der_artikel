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
    Q_PROPERTY(int total_word_count READ totalWordCount NOTIFY totalWordCountChanged)

// Data types
public:

    enum SelectionState_TP {
        NO_SELECTION = 1,
        SINGLE_SELECTION,
        MULTIPLE_SELECTION
    };

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
    void themaSelectionChanged();
    void totalWordCountChanged();

private slots:
    void onThemaItemSelectionChanged();

private:
    void clearThemaList();

private:
    QList<Thema_C*> _thema_list;
    QList<Thema_C*> _selected_thema_list;
    int _total_word_count;
};

#endif // THEMA_MODEL_H
