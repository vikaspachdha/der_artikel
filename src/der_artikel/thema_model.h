#ifndef THEMA_MODEL_H
#define THEMA_MODEL_H

#include <QAbstractListModel>
#include <QList>

class Thema_C;

class ThemaModel_C : public QAbstractListModel
{
    Q_OBJECT

    enum ROLES {
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


signals:
    void themaSelectionChanged();


private slots:
    void OnThemaItemSelectionChanged();


private:
    QList<Thema_C*> _thema_list;
    QList<Thema_C*> _selected_thema_list;

};

#endif // THEMA_MODEL_H
