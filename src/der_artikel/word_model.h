#ifndef WORD_MODEL_H
#define WORD_MODEL_H

#include <QAbstractListModel>
class Word_C;

/**
 * @brief
 *
 */
class WordModel_C : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     */
    enum ROLES_TP {
        WORD_TEXT = Qt::UserRole,
        ARTICLE,
        USER_ARTICLE
    };

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit WordModel_C(QObject *parent = 0);

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
    int rowCount(const QModelIndex &parent) const;
    /**
     * @brief
     *
     * @return QHash<int, QByteArray>
     */
    QHash<int,QByteArray> roleNames() const;

public:
    /**
     * @brief
     *
     * @param words
     */
    void UpdateWords(QList<const Word_C *> words);

signals:

private:
    QList<const Word_C*> _words; /**< TODO */

};

#endif // WORD_MODEL_H
