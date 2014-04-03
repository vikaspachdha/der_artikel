#ifndef WORD_MODEL_H
#define WORD_MODEL_H

#include <QAbstractListModel>
class Word_C;

class WordModel_C : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ROLES_TP {
        WORD_TEXT = Qt::UserRole,
        ARTICLE,
        USER_ARTICLE
    };

public:
    explicit WordModel_C(QObject *parent = 0);

public:
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent) const;
    QHash<int,QByteArray> roleNames() const;

public:
    void UpdateWords(QList<const Word_C *> words);

signals:

private:
    QList<const Word_C*> _words;

};

#endif // WORD_MODEL_H
