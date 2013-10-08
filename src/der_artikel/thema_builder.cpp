#include "thema_builder.h"
#include "ui_thema_builder.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFile>
#include <QDebug>

#include "data/thema.h"
#include "common.h"

ThemaBuilder_C::ThemaBuilder_C(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemaBuilder_C)
{
    ui->setupUi(this);

    _thema = new Thema_C();

    connect(ui->_btn_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnDlgButtonClicked(QAbstractButton*)) );
    connect(ui->_save_btn,SIGNAL(clicked()), this,SLOT(OnSave()) );
    connect(ui->_add_btn,SIGNAL(clicked()), this,SLOT(OnAddClicked()) );
    connect(ui->_word_edit,SIGNAL(textChanged(QString)), this, SLOT(OnWordTextChanged(QString)));
    connect(ui->_thema_name_edit,SIGNAL(textChanged(QString)), this, SLOT(OnThemaNameChanged(QString)));
    connect(ui->_word_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(OnItemDoubleClicked(QListWidgetItem*)) );

    ui->_add_btn->setEnabled(false);
    ui->_save_btn->setEnabled(false);
}

ThemaBuilder_C::~ThemaBuilder_C()
{
    delete ui;
    delete _thema;
}

void ThemaBuilder_C::OnDlgButtonClicked(QAbstractButton *btn)
{
    if(ui->_btn_box->standardButton(btn) == QDialogButtonBox::Close) {
        close();
    }
}

void ThemaBuilder_C::OnAddClicked()
{
    QString text = ui->_word_edit->text();

    Q_ASSERT(!text.isEmpty());
    Q_ASSERT(_thema);

    ARTIKEL::Artikel article = ARTIKEL::NA;
    if(ui->_die_radio->isChecked()) {
        article = ARTIKEL::DIE;
    } else if(ui->_der_radio->isChecked()) {
        article = ARTIKEL::DER;
    } else if(ui->_das_radio->isChecked()) {
        article = ARTIKEL::DAS;
    }

    Word_C* new_word = new Word_C();
    new_word->_artikel = article;
    new_word->_text = text;

    QString listItemText;
    if(article == ARTIKEL::NA) {
        listItemText = text;
    } else {
        listItemText = QString("%1 %2").arg(ARTIKEL::ArtikelText(article)).arg(text);
    }

    QListWidgetItem* list_item = new QListWidgetItem(listItemText,ui->_word_list);
    list_item->setData(Qt::UserRole,QVariant::fromValue<Word_C*>(new_word));

    ui->_word_list->addItem(list_item);
    _thema->_words.append(new_word);
}

void ThemaBuilder_C::OnWordTextChanged(QString new_text)
{
    ui->_add_btn->setEnabled(!new_text.isEmpty());
}

void ThemaBuilder_C::OnThemaNameChanged(QString new_text)
{
    ui->_save_btn->setEnabled(!new_text.isEmpty());
}

void ThemaBuilder_C::OnItemDoubleClicked(QListWidgetItem *item)
{
    if(item)
    {
        Word_C* word = item->data(Qt::UserRole).value<Word_C*>();
        qDebug()<<word->GetWordText();
    }
}

void ThemaBuilder_C::OnSave()
{
    QString save_file = QFileDialog::getSaveFileName(this,tr("Select file name"),
                                                     QDir::homePath() + QDir::separator() + "untitled.AKL",
                                                     tr("Thema files (*.AKL);; All files (*.*)"));

    if(!save_file.isEmpty()) {
        QFile file(save_file);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            Write(&file);
        } else {
            qDebug()<<QString("cannot write file %1:\n%2.") .arg(save_file) .arg(file.errorString());
        }
    }
}

bool ThemaBuilder_C::Write(QIODevice* pDevice)
{
    Q_ASSERT(_thema);

    QDomDocument domDocument("DerArtikel");

    QTextStream out(pDevice);
    QDomElement root = domDocument.createElement("Root");
    root.setAttribute("Version", "1.0");

    _thema->SetText(ui->_thema_name_edit->text().trimmed());
    _thema->SetTrText(ui->_theam_tr_name_edit->text().trimmed());
    _thema->Write(root);

    domDocument.appendChild(root);
    domDocument.save(out, 4);

    return true;
}
