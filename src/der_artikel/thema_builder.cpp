#include "thema_builder.h"
#include "ui_thema_builder.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFile>
#include <QDebug>

#include "data/thema.h"
#include "common.h"
#include "version.h"
#include "thema_loader.h"

ThemaBuilder_C::ThemaBuilder_C(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemaBuilder_C)
{
    ui->setupUi(this);

    _thema = new Thema_C();

    // Connections
    connect(ui->_btn_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnDlgButtonClicked(QAbstractButton*)) );
    connect(ui->_open_btn,SIGNAL(clicked()), this,SLOT(OnLoad()) );
    connect(ui->_save_btn,SIGNAL(clicked()), this,SLOT(OnSave()) );
    connect(ui->_add_btn,SIGNAL(clicked()), this,SLOT(OnAddClicked()) );
    connect(ui->_word_edit,SIGNAL(textChanged(QString)), this, SLOT(OnWordTextChanged(QString)));
    connect(ui->_thema_name_edit,SIGNAL(textChanged(QString)), this, SLOT(OnThemaNameChanged(QString)));
    connect(ui->_word_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(OnItemDoubleClicked(QListWidgetItem*)) );
    connect(ui->_word_list,SIGNAL(itemSelectionChanged()), this, SLOT(OnWordSelectionChanged()));
    connect(ui->_delete_btn,SIGNAL(clicked()), this, SLOT(OnDelete()) );


    // Disable buttons. Enable only when pre-conditions are met.
    ui->_add_btn->setEnabled(false);
    ui->_save_btn->setEnabled(false);
    ui->_delete_btn->setEnabled(false);
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

void ThemaBuilder_C::OnLoad()
{
    QString file_path = QFileDialog::getOpenFileName(this,tr("Select file name"),
                                                     QDir::homePath() + QDir::separator() + "untitled.AKL",
                                                     tr("Thema files (*.AKL);; All files (*.*)"));
    if(!file_path.isEmpty()) {
        ThemaLoader_C loader;
        Thema_C* new_thema = loader.LoadThema(file_path);
        if(new_thema) {
            if(_thema) {
                delete _thema;
            }
            ResetUI();
            _thema = new_thema;
            PopulateUI(_thema);
        }
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
    AddWordToList(new_word);
    _thema->_words.append(new_word);
    ui->_word_edit->setText("");
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

void ThemaBuilder_C::OnWordSelectionChanged()
{
    QList<QListWidgetItem*> selected_items = ui->_word_list->selectedItems();
    ui->_delete_btn->setEnabled(selected_items.count() > 0);
}

void ThemaBuilder_C::OnDelete()
{
    if(_thema) {
        QList<QListWidgetItem*> selected_items = ui->_word_list->selectedItems();
        foreach( QListWidgetItem* item, selected_items ) {
            if(item)
            {
                Word_C* word = item->data(Qt::UserRole).value<Word_C*>();
                if(word) {
                    _thema->_words.remove(_thema->_words.indexOf(word));
                    delete word;
                    delete item;
                }
            }
        }
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
    root.setAttribute("Version", QString::number(APP_VERSION));

    _thema->SetText(ui->_thema_name_edit->text().trimmed());
    _thema->SetTrText(ui->_theam_tr_name_edit->text().trimmed());
    _thema->Write(root);

    domDocument.appendChild(root);
    domDocument.save(out, 4);

    return true;
}

void ThemaBuilder_C::AddWordToList(Word_C* new_word)
{
    if(new_word) {
        QString listItemText;
        if(new_word->_artikel == ARTIKEL::NA) {
            listItemText = new_word->_text;
        } else {
            listItemText = QString("%1 %2").arg(ARTIKEL::ArtikelText(new_word->_artikel)).arg(new_word->_text);
        }

        QListWidgetItem* list_item = new QListWidgetItem(listItemText,ui->_word_list);
        list_item->setData(Qt::UserRole,QVariant::fromValue<Word_C*>(new_word));

        ui->_word_list->addItem(list_item);
    }
}

void ThemaBuilder_C::ResetUI()
{
    ui->_thema_name_edit->setText("");
    ui->_thema_name_edit->setText("");
    ui->_word_edit->setText("");
    ui->_word_list->clear();
    ui->_thema_name_edit->setFocus();
}

void ThemaBuilder_C::PopulateUI(Thema_C *thema)
{
    if(thema) {
        ui->_thema_name_edit->setText(thema->GetText());
        ui->_theam_tr_name_edit->setText(thema->GetTrText());
        foreach(Word_C* word, thema->_words) {
            AddWordToList(word);
        }
    }
}
