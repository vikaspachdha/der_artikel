#include "conflict_dlg.h"
#include "ui_conflict_dlg.h"
#include "data/word.h"
#include "data/article.h"
#include <QDesktopWidget>
#include <QApplication>
#include <QShowEvent>
/*!
 \brief

 \param old_word
 \param new_word
 \param parent
*/
ConflictDlg_C::ConflictDlg_C(Word_C &old_word, Word_C &new_word, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConflictDlg_UIC)
{
    ui->setupUi(this);
    connect(ui->_extra_desc_txt,SIGNAL(textChanged(QString)),SLOT(onOptionsChanged()));
    connect(ui->_update_article_chk,SIGNAL(toggled(bool)),SLOT(onOptionsChanged()));
    connect(ui->_update_translation_chk,SIGNAL(toggled(bool)),SLOT(onOptionsChanged()));

    QString warning_text = QString("Word \"%1\" already exists.").arg(new_word.wordText());
    bool isSame = true;
    if(old_word.artikel() != new_word.artikel()) {
        warning_text.append(QString("\n\nOld article is \"%1\" and new article is \"%2\".")
                .arg(Article_C::ArtikelText(old_word.artikel()))
                .arg(Article_C::ArtikelText(new_word.artikel())) );
        isSame = false;
    } else {
        ui->_update_article_chk->setVisible(false);
    }

    if(old_word.description() != new_word.description()) {
        warning_text.append(QString("\n\nOld description is \"%1\" and new description is \"%2\".")
                .arg(old_word.description())
                .arg(new_word.description()) );
        isSame = false;
    } else {
        ui->_update_translation_chk->setVisible(false);
        ui->_extra_desc_txt->setVisible(false);
        ui->_extra_desc_lbl->setVisible(false);
    }

    if(isSame) {
        warning_text.append("\n Same words are not allowed.");
        ui->_btn_box->setStandardButtons(QDialogButtonBox::Ok);
    }
    ui->_msg_lbl->setText(warning_text);
    adjustSize();
}

/*!
 \brief

*/
ConflictDlg_C::~ConflictDlg_C()
{
    delete ui;
}

/*!
 \brief

 \return bool
*/
bool ConflictDlg_C::updateArticle() const
{
    return ui->_update_article_chk->isChecked();
}

/*!
 \brief

 \return bool
*/
bool ConflictDlg_C::updateDescription() const
{
    return ui->_update_translation_chk->isChecked();
}

QString ConflictDlg_C::extraDescription() const
{
    return ui->_extra_desc_txt->text();
}

void ConflictDlg_C::moveEvent(QMoveEvent *event)
{
    Q_UNUSED(event);
    QRect aRect = QApplication::desktop()->availableGeometry(this);
    move(aRect.center() -rect().center());
}

void ConflictDlg_C::onOptionsChanged()
{
    ui->_discard_lbl->setVisible(ui->_extra_desc_txt->text().isEmpty() &&
                                 !ui->_update_article_chk->isChecked() &&
                                 !ui->_update_translation_chk->isChecked());
}
