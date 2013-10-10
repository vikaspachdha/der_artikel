#include "thema_builder.h"
#include "ui_thema_builder.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QFile>
#include <QShortcut>
#include <QKeyEvent>
#include <QDebug>

#include "data/thema.h"
#include "common.h"
#include "version.h"
#include "thema_loader.h"

ThemaBuilder_C::ThemaBuilder_C(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemaBuilder_C),
    _edit_item(0)
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

    connect(ui->_a_umlaut_btn, SIGNAL(clicked()), SLOT(InsertAUmlaut()));
    connect(ui->_o_umlaut_btn, SIGNAL(clicked()), SLOT(InsertOUmlaut()));
    connect(ui->_u_umlaut_btn, SIGNAL(clicked()), SLOT(InsertUUmlaut()));
    connect(ui->_eszett_btn, SIGNAL(clicked()), SLOT(InsertEszett()));

    // Shortcut for a & A umlaut chars
    QShortcut* a_umlaut_shortcut =  new QShortcut(this);
    a_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::Key_A));
    connect(a_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertAUmlaut()));

    QShortcut* caps_a_umlaut_shortcut =  new QShortcut(this);
    caps_a_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_A));
    connect(caps_a_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertAUmlaut()));


    // Shortcut for o & O umlaut chars
    QShortcut* o_umlaut_shortcut =  new QShortcut(this);
    o_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::Key_O));
    connect(o_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertOUmlaut()));

    QShortcut* caps_o_umlaut_shortcut =  new QShortcut(this);
    caps_o_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_O));
    connect(caps_o_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertOUmlaut()));


    // Shortcut for u & U umlaut chars
    QShortcut* u_umlaut_shortcut =  new QShortcut(this);
    u_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::Key_U));
    connect(u_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertUUmlaut()));

    QShortcut* caps_u_umlaut_shortcut =  new QShortcut(this);
    caps_u_umlaut_shortcut->setKey(QKeySequence(Qt::ALT + Qt::SHIFT + Qt::Key_U));
    connect(caps_u_umlaut_shortcut, SIGNAL(activated()), SLOT(InsertUUmlaut()));


    // Shortcut for eszett char
    QShortcut* eszett_shortcut =  new QShortcut(this);
    eszett_shortcut->setKey(QKeySequence(Qt::ALT + Qt::Key_S));
    connect(eszett_shortcut, SIGNAL(activated()), SLOT(InsertEszett()));

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

void ThemaBuilder_C::keyPressEvent(QKeyEvent *e)
{
    if(e && e->key() == Qt::Key_Shift) {
        SetUmlautUpperCase(true);
    }
}

void ThemaBuilder_C::keyReleaseEvent(QKeyEvent *e)
{
    if(e && e->key() == Qt::Key_Shift) {
        SetUmlautUpperCase(false);
    }
}

void ThemaBuilder_C::OnDlgButtonClicked(QAbstractButton *btn)
{
    if(ui->_btn_box->standardButton(btn) == QDialogButtonBox::Close) {
        close();
    }
}

void ThemaBuilder_C::OnLoad()
{
    static QString last_open_path = QDir::homePath();
    QString file_path = QFileDialog::getOpenFileName(this,tr("Select file name"),
                                                     last_open_path,
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
            last_open_path = file_path;
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

    if(_edit_item) {
        Word_C* edit_word = _edit_item->data(Qt::UserRole).value<Word_C*>();
        edit_word->_artikel = article;
        edit_word->_text = text;
        UpdateItem(_edit_item);
        SetWordUiState(ADD_STATE);
    } else {
        Word_C* new_word = new Word_C();
        new_word->_artikel = article;
        new_word->_text = text;
        AddWordToList(new_word);
        _thema->_words.append(new_word);
    }

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
        if(word) {
            _edit_item = item;

            ui->_word_edit->setText(word->GetWordText());

            switch(word->GetArtikel()) {
            case ARTIKEL::DAS:
                ui->_das_radio->setChecked(true);
                break;
            case ARTIKEL::DER:
                ui->_der_radio->setChecked(true);
                break;
            case ARTIKEL::DIE:
                ui->_die_radio->setChecked(true);
                break;
            case ARTIKEL::NA:
                ui->_na_radio->setChecked(true);
                break;
            default:
                break;
            }

            SetWordUiState(UPDATE_STATE);
        }
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
                if(_edit_item == item) {
                    SetWordUiState(ADD_STATE);

                }
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

void ThemaBuilder_C::InsertAUmlaut()
{
    if(QApplication::keyboardModifiers() & Qt::SHIFT) {
        InsertSplText("Ä");
    } else {
        InsertSplText("ä");
    }
}

void ThemaBuilder_C::InsertOUmlaut()
{
    if(QApplication::keyboardModifiers() & Qt::SHIFT) {
        InsertSplText("Ö");
    } else {
        InsertSplText("ö");
    }
}

void ThemaBuilder_C::InsertUUmlaut()
{
    if(QApplication::keyboardModifiers() & Qt::SHIFT) {
        InsertSplText("Ü");
    } else {
        InsertSplText("ü");
    }
}

void ThemaBuilder_C::InsertEszett()
{
    InsertSplText("ß");
}

void ThemaBuilder_C::UpdateItem(QListWidgetItem *item)
{
    if(item) {
        Word_C* word = item->data(Qt::UserRole).value<Word_C*>();
        if(word) {
            QString listItemText;
            if(word->_artikel == ARTIKEL::NA) {
                listItemText = word->_text;
            } else {
                listItemText = QString("%1 %2").arg(ARTIKEL::ArtikelText(word->_artikel)).arg(word->_text);
            }
            item->setText(listItemText);
        }
    }
}

void ThemaBuilder_C::OnSave()
{
    static QString last_save_path = QDir::homePath() + QDir::separator() + "untitled.AKL";
    QString save_file = QFileDialog::getSaveFileName(this,tr("Select file name"),
                                                     last_save_path,
                                                     tr("Thema files (*.AKL);; All files (*.*)"));

    if(!save_file.isEmpty()) {
        QFile file(save_file);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            if(Write(&file)) {
                last_save_path = save_file;
            }
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
        QListWidgetItem* list_item = new QListWidgetItem(ui->_word_list);
        list_item->setData(Qt::UserRole,QVariant::fromValue<Word_C*>(new_word));
        UpdateItem(list_item);
        ui->_word_list->addItem(list_item);
    }
}

void ThemaBuilder_C::ResetUI()
{
    ui->_thema_name_edit->setText("");
    ui->_theam_tr_name_edit->setText("");
    ui->_word_edit->setText("");
    ui->_na_radio->setChecked(true);
    ui->_word_list->clear();
    SetWordUiState(ADD_STATE);
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

void ThemaBuilder_C::SetWordUiState(ThemaBuilder_C::WordUIState new_state)
{
    if(new_state == ADD_STATE) {
        _edit_item = 0;
        ui->_add_btn->setText(tr("Add"));
        ui->_word_edit->setText("");
        ui->_na_radio->setChecked(true);
    } else {
        ui->_add_btn->setText(tr("Update"));
    }
}

void ThemaBuilder_C::InsertSplText(QString str)
{
    QWidget* widget = QApplication::focusWidget();
    QLineEdit* editor = dynamic_cast<QLineEdit*>(widget);
    if(editor) {
        editor->insert(str);
    }
}

void ThemaBuilder_C::SetUmlautUpperCase(bool upper_case)
{
    if(upper_case) {
        ui->_a_umlaut_btn->setText("Ä");
        ui->_o_umlaut_btn->setText("Ö");
        ui->_u_umlaut_btn->setText("Ü");
    } else {
        ui->_a_umlaut_btn->setText("ä");
        ui->_o_umlaut_btn->setText("ö");
        ui->_u_umlaut_btn->setText("ü");
    }
}
