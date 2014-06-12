#ifndef WORD_LIST_ITEM_H
#define WORD_LIST_ITEM_H

#include <QListWidgetItem>

class WordListItem_C : public QListWidgetItem
{
public:
    explicit WordListItem_C(QListWidget * parent = 0, int type = Type);

public:
    virtual bool operator<(const QListWidgetItem & other) const;
};

#endif // WORD_LIST_ITEM_H
