#include "thema_model.h"

ThemaModel_C::ThemaModel_C(QVector<Thema_C *> thema_list, QObject *parent):
    QAbstractItemModel(parent),
    _thema_list(thema_list)
{

}

QVariant ThemaModel_C::data(const QModelIndex &index, int role) const
{
    QVariant data;
    return data;
}

int ThemaModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _thema_list.count();
}
