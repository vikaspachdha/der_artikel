#include "word_model.h"
#include "data/word.h"

/*!
 \brief

 \param parent
*/
WordModel_C::WordModel_C(QObject *parent) :
    QAbstractListModel(parent)
{
}

/*!
 \brief

 \param index
 \param role
 \return QVariant
*/
QVariant WordModel_C::data(const QModelIndex &index, int role) const
{
    QVariant data;
    if(index.isValid()) {
        int row = index.row();
        const Word_C* word = 0;
        if( (row>=0) && row < _words.count() ) {
            word = _words.at(row);
        }

        if(word) {
            switch (role) {
            case WORD_TEXT:
                data = word->GetWordText();
                break;
            case ARTICLE:
                data = word->GetArtikel();
                break;
            case USER_ARTICLE:
                data = word->GetUserArtikel();
                break;
            default:
                break;
            }
        }
    }
    return data;
}

/*!
 \brief

 \param parent
 \return int
*/
int WordModel_C::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return _words.count();
}

/*!
 \brief

 \return QHash<int, QByteArray>
*/
QHash<int, QByteArray> WordModel_C::roleNames() const
{
    QHash<int,QByteArray> roleNames;
    roleNames[WORD_TEXT] = "word_text";
    roleNames[ARTICLE] = "article";
    roleNames[USER_ARTICLE] = "user_article";
    return roleNames;
}

/*!
 \brief

 \param words
*/
void WordModel_C::UpdateWords(QList<const Word_C *> words)
{
    beginResetModel();
    _words.clear();
    _words = words;
    endResetModel();
}
