#ifndef THEMA_MODEL_H
#define THEMA_MODEL_H

#include <QAbstractItemModel>
#include <QVector>

class Thema_C;

class ThemaModel_C : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ThemaModel_C(QVector<Thema_C*> thema_list, QObject *parent = 0);

public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;

private:
    QVector<Thema_C*>& _thema_list;

};

#endif // THEMA_MODEL_H
