#include "word_list_item.h"
#include <QString>

WordListItem_C::WordListItem_C(QListWidget *parent, int type) :
    QListWidgetItem(parent, type)
{
}

bool WordListItem_C::operator<(const QListWidgetItem &other) const
{
    return data(NOUN_ROLE).toString() < other.data(NOUN_ROLE).toString();
}
