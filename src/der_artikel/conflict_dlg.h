#ifndef CONFLICT_DLG_H
#define CONFLICT_DLG_H

#include <QDialog>

namespace Ui {
class ConflictDlg_C;
}
class Word_C;
/**
 * @brief
 *
 */
class ConflictDlg_C : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief
     *
     * @param old_word
     * @param new_word
     * @param parent
     */
    explicit ConflictDlg_C(Word_C& old_word, Word_C& new_word, QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~ConflictDlg_C();

public:
    /**
     * @brief
     *
     * @return bool
     */
    bool updateArticle() const;
    /**
     * @brief
     *
     * @return bool
     */
    bool updateTranslation() const;

private:
    Ui::ConflictDlg_C *ui; /**< TODO */
};

#endif // CONFLICT_DLG_H
