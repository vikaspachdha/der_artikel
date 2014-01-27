#ifndef THEMA_MODEL_H
#define THEMA_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "data/thema.h"

/**
 * @brief
 *
 */
class ThemaModel_C : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(SelectionState_TP)

    // Properties
    Q_PROPERTY(SelectionState_TP selection_state READ SelectionState NOTIFY themaSelectionChanged)
    Q_PROPERTY(Thema_C* selected_thema READ GetSelectedThema NOTIFY themaSelectionChanged)

// Data types
public:

    /**
     * @brief
     *
     */
    enum SelectionState_TP {
        NO_SELECTION = 1,
        SINGLE_SELECTION,
        MULTIPLE_SELECTION
    };

    /**
     * @brief
     *
     */
    enum ROLES_TP {
        DISPLAY_NAME=Qt::UserRole+1,
        TR_NAME,
        AUTHOR,
        SELECTED,
        EXPERIENCE,
        WORD_COUNT,
        THEMA_STATE,
        THEMA_OBJECT
    };


public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit ThemaModel_C(QObject *parent = 0);
    /**
     * @brief
     *
     */
    ~ThemaModel_C();

// QAbstarctItemModel Implementation.
public:
    /**
     * @brief
     *
     * @param index
     * @param role
     * @return QVariant
     */
    QVariant data(const QModelIndex &index, int role) const;
    /**
     * @brief
     *
     * @param parent
     * @return int
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    /**
     * @brief
     *
     * @return QHash<int, QByteArray>
     */
    QHash<int,QByteArray> roleNames() const;
    /**
     * @brief
     *
     * @param index
     * @return Qt::ItemFlags
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;
    /**
     * @brief
     *
     * @param index
     * @param value
     * @param role
     * @return bool
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

public:
    /**
     * @brief
     *
     * @param new_thema
     */
    void AddThema(Thema_C* new_thema);
    /**
     * @brief
     *
     * @return Thema_C
     */
    Thema_C* GetSelectedThema();
    /**
     * @brief
     *
     */
    void ClearSelection();
    /**
     * @brief
     *
     * @return SelectionState_TP
     */
    SelectionState_TP SelectionState() const;

signals:
    /**
     * @brief
     *
     */
    void themaSelectionChanged();


private slots:
    /**
     * @brief
     *
     * @param type
     */
    void OnThemaItemSelectionChanged(Thema_C::SelectionType_TP type);


private:
    QList<Thema_C*> _thema_list; /**< TODO */
    QList<Thema_C*> _selected_thema_list; /**< TODO */
};

#endif // THEMA_MODEL_H
