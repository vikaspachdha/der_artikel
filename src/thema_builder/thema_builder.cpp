#include "thema_builder.h"
#include "ui_thema_builder.h"

#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QIntValidator>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>
#include <QTextStream>

#include "conflict_dlg.h"
#include "data/common.h"
#include "data/thema.h"
#include "data/thema_loader.h"
#include "data/version.h"
#include "log4qt/log_defines.h"
#include "word_list_item.h"

ThemaBuilder_C::ThemaBuilder_C(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemaBuilder_UIC),
    _edit_item(0)
{
    ui->setupUi(this);

    QSettings::setDefaultFormat(QSettings::IniFormat);

    QIntValidator* points_validator = new QIntValidator(ui->_points_edit);
    points_validator->setBottom(0);
    ui->_points_edit->setValidator(points_validator);

    showPrivateDataControls(false);

    ui->_author_name_edit->setText(UserName());

    _thema = new Thema_C();

    // Connections
    connect(ui->_private_data_btn,SIGNAL(toggled(bool)),SLOT(showPrivateDataControls(bool)));
    connect(ui->_btn_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnDlgButtonClicked(QAbstractButton*)) );
    connect(ui->_new_btn,SIGNAL(clicked()), this,SLOT(OnNew()) );
    connect(ui->_open_btn,SIGNAL(clicked()), this,SLOT(OnLoad()) );
    connect(ui->_save_btn,SIGNAL(clicked()), this,SLOT(OnSave()) );
    connect(ui->_save_as_btn,SIGNAL(clicked()), this,SLOT(OnSaveAs()) );
    connect(ui->_icon_btn,SIGNAL(clicked()), this,SLOT(OnIcon()) );
    connect(ui->_export_data_btn,SIGNAL(clicked()), this,SLOT(OnExport()) );
    connect(ui->_import_data_btn,SIGNAL(clicked()), this,SLOT(OnImport()) );
    connect(ui->_add_btn,SIGNAL(clicked()), this,SLOT(OnAddClicked()) );
    connect(ui->_word_edit,SIGNAL(textChanged(QString)), this, SLOT(OnWordTextChanged(QString)));
    connect(ui->_thema_name_edit,SIGNAL(textChanged(QString)), this, SLOT(updateSaveBtns()));
    connect(ui->_thema_tr_name_edit,SIGNAL(textChanged(QString)), this, SLOT(updateSaveBtns()));
    connect(ui->_word_list,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(OnItemDoubleClicked(QListWidgetItem*)) );
    connect(ui->_word_list,SIGNAL(itemSelectionChanged()), this, SLOT(OnWordSelectionChanged()));
    connect(ui->_delete_btn,SIGNAL(clicked()), this, SLOT(OnDelete()) );
    connect(ui->_index_btn,SIGNAL(clicked()),this,SLOT(OnIndex()));
    connect(ui->_export_icon_btn,SIGNAL(clicked()),this,SLOT(onExportIcon()));


    connect(ui->_a_umlaut_btn, SIGNAL(clicked()), SLOT(InsertAUmlaut()));
    connect(ui->_o_umlaut_btn, SIGNAL(clicked()), SLOT(InsertOUmlaut()));
    connect(ui->_u_umlaut_btn, SIGNAL(clicked()), SLOT(InsertUUmlaut()));
    connect(ui->_eszett_btn, SIGNAL(clicked()), SLOT(InsertEszett()));

    connect(ui->_enable_update_date_chk,SIGNAL(toggled(bool)),this,SLOT(onEnableDateTimeChk(bool)));

    _date_time_timer.setInterval(1000);
    connect(&_date_time_timer,SIGNAL(timeout()),this,SLOT(onUpdateTime()));
    _date_time_timer.start();

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
    ui->_save_as_btn->setEnabled(false);
    ui->_export_data_btn->setEnabled(false);
    ui->_delete_btn->setEnabled(false);
    ui->_update_date_time_edit->setEnabled(false);
    ui->_update_date_time_edit->setDateTime(QDateTime::currentDateTime());
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

void ThemaBuilder_C::OnNew()
{
    Reset();
    LOG_INFO("Thema builder :: New thema.");
    _thema = new Thema_C();
}

void ThemaBuilder_C::OnLoad()
{
    static QString last_open_path = lastPath(LOAD_PATH);
    QString file_path = QFileDialog::getOpenFileName(this,tr("Select file name"),
                                                     last_open_path,
                                                     tr("Thema files (*.AKL);; All files (*.*)"));
    if(!file_path.isEmpty()) {
        ThemaLoader_C loader;
        Thema_C* new_thema = loader.loadThema(file_path,false);
        if(new_thema) {
            LOG_INFO("Thema builder :: New thema loaded.");
            Reset();
            _thema = new_thema;
            PopulateUI(_thema);
            last_open_path = file_path;
            saveLastPath(LOAD_PATH,QFileInfo(last_open_path).absolutePath());
        }
    }

}

void ThemaBuilder_C::OnSave()
{
    QString save_file = _thema ? _thema->filePath():"";
    if(save_file.isEmpty()) {
        OnSaveAs();
    } else {
        Save(save_file);
    }
}

void ThemaBuilder_C::OnSaveAs()
{
    static QString last_save_path = lastPath(SAVE_PATH) + QDir::separator() + "untitled.AKL";
    QString save_file = QFileDialog::getSaveFileName(this,tr("Select file name"),
                                                     last_save_path,
                                                     tr("Thema files (*.AKL);; All files (*.*)"));

    if(Save(save_file)) {
        last_save_path = save_file;
        saveLastPath(SAVE_PATH, QFileInfo(last_save_path).absolutePath());
    }
}

void ThemaBuilder_C::OnAddClicked()
{
    QString text = ARTIKEL::capitalize(ui->_word_edit->text().trimmed());
    QString desc = ARTIKEL::capitalize(ui->_desc_edit->text().trimmed());

    Q_ASSERT(!text.isEmpty());
    Q_ASSERT(_thema);

    Article_C::Artikel article = Article_C::NA;
    if(ui->_die_radio->isChecked()) {
        article = Article_C::DIE;
    } else if(ui->_der_radio->isChecked()) {
        article = Article_C::DER;
    } else if(ui->_das_radio->isChecked()) {
        article = Article_C::DAS;
    }

    QListWidgetItem* new_item = 0;
    if(_edit_item) {
        Word_C* edit_word = _edit_item->data(WordListItem_C::WORD_ROLE).value<Word_C*>();

        Word_C* old_word = new Word_C();
        old_word->_artikel = edit_word->_artikel;
        old_word->_text = edit_word->_text;
        old_word->_description = edit_word->_description;

        deleteItem(_edit_item);

        Word_C* new_word = new Word_C();
        new_word->_artikel = article;
        new_word->_text = text;
        new_word->_description = desc;

        if(AddWordToThema(new_word)) {
            delete old_word;
            new_item = _word_item_hash[new_word];
        } else {
            delete new_word;
            AddWordToThema(old_word);
        }

        //SetWordUiState(ADD_STATE);
    } else {
        Word_C* new_word = new Word_C();
        new_word->_artikel = article;
        new_word->_text = text;
        new_word->_description = desc;
        if(!AddWordToThema(new_word)) {
            delete new_word;
        } else {
            new_item = _word_item_hash[new_word];
        }
    }

    ui->_word_edit->setText("");
    ui->_desc_edit->setText("");
    if(new_item) {
        new_item->setSelected(true);
        ui->_word_list->scrollToItem(new_item);
    }
}

void ThemaBuilder_C::OnWordTextChanged(QString new_text)
{
    ui->_add_btn->setEnabled(!new_text.isEmpty());
}

void ThemaBuilder_C::OnItemDoubleClicked(QListWidgetItem *item)
{
    if(item)
    {
        Word_C* word = item->data(WordListItem_C::WORD_ROLE).value<Word_C*>();
        if(word) {
            _edit_item = item;

            ui->_word_edit->setText(word->wordText());
            ui->_desc_edit->setText(word->description());

            switch(word->artikel()) {
            case Article_C::DAS:
                ui->_das_radio->setChecked(true);
                break;
            case Article_C::DER:
                ui->_der_radio->setChecked(true);
                break;
            case Article_C::DIE:
                ui->_die_radio->setChecked(true);
                break;
            case Article_C::NA:
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
            deleteItem(item);
        }
        UpdateUI();
    }
}

void ThemaBuilder_C::OnIndex()
{
    static QString last_open_path = lastPath(INDEX_PATH);
    QString file_path = QFileDialog::getExistingDirectory(this, tr("Open Thema Directory"),
                                                          last_open_path,
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    if(!file_path.isEmpty()) {
        last_open_path = file_path;
        saveLastPath(INDEX_PATH,last_open_path);
        QDir root_thema_dir = file_path;
        QStringList nameFilters;
        nameFilters<<"*.AKL";
        QFileInfoList thema_files= root_thema_dir.entryInfoList(nameFilters,QDir::Files | QDir::NoSymLinks|QDir::NoDotAndDotDot);
        QFile index_file(file_path + QDir::separator() + "index.csv");
        if(index_file.open(QIODevice::WriteOnly)) {
            QTextStream write_stream(&index_file);
            write_stream.setCodec("UTF-8");
            write_stream<<ARTIKEL::INDEX_FILE_TOKEN<<endl;
            ThemaLoader_C thema_loader;
            foreach(QFileInfo thema_file, thema_files) {
                Thema_C* thema = thema_loader.loadThema(thema_file.absoluteFilePath());
                if(thema) {
                    QDateTime update_stamp = thema->lastUpdated();
                    write_stream<<thema_file.fileName()<<";"<<QString::number(update_stamp.toMSecsSinceEpoch())<<endl;
                }
            }
            index_file.close();
            QMessageBox::information(this,tr("Indexing complete"),tr("Indexing finished."),QMessageBox::Ok);
        } else {
            QMessageBox::information(this,tr("Error"),tr("Error writing index file : %1").arg(index_file.errorString()),QMessageBox::Ok);
        }

    }
}

void ThemaBuilder_C::onExportIcon()
{
    static QString last_export_path = lastPath(ICON_EXPORT_PATH);
    const QPixmap* icon = ui->_icon_lbl->pixmap();
    if(icon && !icon->isNull()) {
        QString save_file = QFileDialog::getSaveFileName(this,tr("Select file name"),
                                                         last_export_path,
                                                         tr("Png files (*.png);; All files (*.*)"));
        if(!save_file.isEmpty()) {
            last_export_path = save_file;
            saveLastPath(ICON_EXPORT_PATH, last_export_path);
            icon->save(save_file);
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

void ThemaBuilder_C::onEnableDateTimeChk(bool enabled)
{
    ui->_update_date_time_edit->setEnabled(enabled);
    if(enabled) {
        _date_time_timer.stop();
    } else {
        ui->_update_date_time_edit->setDateTime(QDateTime::currentDateTime());
        _date_time_timer.start();
    }
}

void ThemaBuilder_C::onUpdateTime()
{
    ui->_update_date_time_edit->setDateTime(QDateTime::currentDateTime());
}

void ThemaBuilder_C::showPrivateDataControls(bool show)
{
    ui->_update_date_time_edit->setVisible(show);
    ui->_enable_update_date_chk->setVisible(show);
    ui->_update_lbl->setVisible(show);
    ui->_points_edit->setVisible(show);
    ui->_last_played_date_time_edit->setVisible(show);
    ui->_last_played_lbl->setVisible(show);
    ui->_points_lbl->setVisible(show);
    ui->_last_played_clear_chk->setVisible(show);
    ui->_export_icon_btn->setVisible(show);
    if(!show) {
        ui->_last_played_clear_chk->setChecked(false);
    }
}

void ThemaBuilder_C::UpdateItem(QListWidgetItem *item)
{
    if(item) {
        Word_C* word = item->data(WordListItem_C::WORD_ROLE).value<Word_C*>();
        if(word) {
            QString listItemText;
            if(word->_artikel == Article_C::NA) {
                listItemText = word->_text;
            } else {
                listItemText = QString("%1 %2").arg(Article_C::ArtikelText(word->_artikel)).arg(word->_text);
            }
            item->setText(listItemText);
            item->setData(WordListItem_C::NOUN_ROLE,word->_text);
        }
    }
}

bool ThemaBuilder_C::Save(QString save_file)
{
    Q_ASSERT(_thema);

    _thema->_text = ui->_thema_name_edit->text().trimmed();
    _thema->_translation =  ui->_thema_tr_name_edit->text().trimmed();
    _thema->_author = ui->_author_name_edit->text().trimmed();
    _thema->_icon = *(ui->_icon_lbl->pixmap());
    _thema->setLastUpdated(ui->_update_date_time_edit->dateTime());

    if(ui->_private_data_btn->isChecked()) {
        _thema->_last_played = ui->_last_played_clear_chk->isChecked() ?
                    QDateTime() : ui->_last_played_date_time_edit->dateTime();
        _thema->_experience_points = ui->_points_edit->text().toInt();
    } else {
        _thema->_last_played = QDateTime();
    }

    bool success = _thema->save(save_file);
    if (success) {
        LOG_INFO(QString("Thema builder :: Saved file to %1") .arg(save_file));
    } else {
        LOG_WARN(QString("Thema builder :: Cannot save file %1.") .arg(save_file));
    }
    return success;
}

void ThemaBuilder_C::OnExport()
{
    static QString last_export_path = lastPath(EXPORT_PATH) + QDir::separator() + "untitled.csv";
    QString save_file = QFileDialog::getSaveFileName(this,tr("Select file name"),
                                                     last_export_path,
                                                     tr("CSV files (*.csv);; All files (*.*)"));
    if(!save_file.isEmpty()) {
        QFile file(save_file);
        if (file.open(QFile::WriteOnly | QFile::Text)) {
            if(Export(&file)) {
                LOG_INFO(QString("Thema builder :: Exported file to %1") .arg(save_file));
                last_export_path = save_file;
                saveLastPath(EXPORT_PATH, QFileInfo(last_export_path).absolutePath());
            } else {
                QMessageBox::critical(this,tr("Export failed"), tr("Invalid file or permissions"));
            }
        } else {
            LOG_WARN(QString("Thema builder :: Cannot export file %1:\n%2.") .arg(save_file).arg(file.errorString()));
        }
    }
}

void ThemaBuilder_C::OnIcon()
{
    static QString last_icon_path = lastPath(ICON_PATH);
    QString file_path = QFileDialog::getOpenFileName(this,tr("Select a png file"),
                                                     last_icon_path,
                                                     tr("Png files (*.png);; All files (*.*)"));
    if(!file_path.isEmpty()) {
        QPixmap p(file_path);
        if(p.isNull()) {
            QMessageBox::warning(this,tr("Invalid Image"), tr("Invalid image file"));
        } else {
            LOG_INFO(QString("Thema builder :: New icon file : %1").arg(file_path));
            p = p.scaled(64,64);
            ui->_icon_lbl->setPixmap(p);
            last_icon_path = file_path;
            saveLastPath(ICON_PATH,QFileInfo(last_icon_path).absolutePath());
        }
    }
}

void ThemaBuilder_C::OnImport()
{
    static QString last_open_path = lastPath(IMPORT_PATH);
    QString file_path = QFileDialog::getOpenFileName(this,tr("Select file to import"),
                                                     last_open_path,
                                                     tr("CSV files (*.csv);; All files (*.*)"));

    if(!file_path.isEmpty()) {
        QFile file(file_path);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            if(Import(&file)) {
                last_open_path = file_path;
                saveLastPath(IMPORT_PATH,QFileInfo(last_open_path).absolutePath());
            } else {
                QMessageBox::critical(this,tr("Import failed"), tr("Invalid file or format"));
            }
        } else {
            LOG_ERROR(QString("Thema builder :: Cannot Import file %1:\n%2.") .arg(file_path) .arg(file.errorString()));
        }
    }
}

bool ThemaBuilder_C::Export(QIODevice *pDevice)
{
    Q_ASSERT(_thema);
    bool success = false;
    if(pDevice) {
        QTextStream out(pDevice);
        out.setCodec("UTF-8");
        foreach(Word_C* word, _thema->_words) {
            out<<word->_artikel<<";"<<word->_text<<";"<<word->_description<<"\n";
        }

        pDevice->close();
        success = true;
    }
    return success;
}

bool ThemaBuilder_C::Import(QIODevice *pDevice)
{
    bool success = false;
    if(pDevice) {
        QTextStream stream(pDevice);
        stream.setCodec("UTF-8");
        QString line;
        int line_count = 0;
        do {
            line = stream.readLine();
            ++line_count;
            QStringList word_data = line.split(";");
            if(word_data.count() > 2) {

                bool ok = false;
                int article_code =  word_data.at(0).toInt(&ok);
                Article_C::Artikel article = Article_C::INVALID;
                if(ok && (article_code >= Article_C::DER) && (article_code< Article_C::INVALID)) {
                    article = (Article_C::Artikel)article_code;
                } else {
                    LOG_DEBUG(QString("ThemaBuilder_C::Import Invalid article code, Line %1").arg(line_count));
                    continue;
                }
                Word_C* new_word = new Word_C();
                new_word->_artikel = article;
                new_word->_text = ARTIKEL::capitalize(word_data.at(1));
                new_word->_description = ARTIKEL::capitalize(word_data.at(2));
                if(!AddWordToThema(new_word)) {
                    delete new_word;
                }
            }
        } while (!line.isNull());
        pDevice->close();
        success = true;
    }
    return success;
}

bool ThemaBuilder_C::AddWordToList(Word_C* new_word)
{
    bool success = false;
    if(new_word) {
        QListWidgetItem* list_item = new WordListItem_C(ui->_word_list);
        list_item->setData(WordListItem_C::WORD_ROLE,QVariant::fromValue<Word_C*>(new_word));
        UpdateItem(list_item);
        ui->_word_list->addItem(list_item);
        _word_item_hash[new_word] = list_item;
        UpdateUI();
        success = true;
    }
    return success;
}

bool ThemaBuilder_C::AddWordToThema(Word_C *new_word)
{
    bool success = false;
    if(new_word) {
        if(_words_set.contains(wordId(new_word))) {
            Word_C* old_word = _words_set[wordId(new_word)];
            LOG_WARN(QString("Thema builder :: Duplicate word %1").arg(new_word->wordText()));
            ConflictDlg_C conflict_dlg(*old_word, *new_word, this);
            if(conflict_dlg.exec() == QDialog::Accepted) {
                QListWidgetItem* list_item = _word_item_hash[old_word];
                Q_ASSERT(list_item);
                if(conflict_dlg.updateArticle()) {
                    old_word->_artikel = new_word->_artikel;
                }
                if(conflict_dlg.updateDescription()) {
                    old_word->_description = new_word->_description;
                }

                if(!conflict_dlg.extraDescription().trimmed().isEmpty()) {
                    old_word->_description.append(QString(", %1").arg(conflict_dlg.extraDescription().trimmed()));
                }
                UpdateItem(list_item);
            }
        } else {
            AddWordToList(new_word);
            _thema->_words.append(new_word);
            _words_set[wordId(new_word)] = new_word;
            success = true;
        }
    }
    return success;
}

void ThemaBuilder_C::Reset()
{
    LOG_DEBUG("ThemaBuilder_C::Reset");
    if(_thema) {
        delete _thema;
        _thema = 0;
    }
    _words_set.clear();
    _word_item_hash.clear();
    ui->_thema_name_edit->setText("");
    ui->_thema_tr_name_edit->setText("");
    ui->_word_edit->setText("");
    ui->_desc_edit->setText("");
    ui->_na_radio->setChecked(true);
    ui->_word_list->clear();
    ui->_icon_lbl->setPixmap(QPixmap());
    SetWordUiState(ADD_STATE);
    UpdateUI();
}

void ThemaBuilder_C::UpdateUI()
{
    int word_count = ui->_word_list->count();
    ui->_word_count_lbl->setText(QString::number(word_count));
    if(word_count > 0) {
        ui->_export_data_btn->setEnabled(true);
    } else {
        ui->_export_data_btn->setEnabled(false);
    }
}

void ThemaBuilder_C::updateSaveBtns()
{
    bool enable = true;
    if(ui->_thema_name_edit->text().isEmpty() || ui->_thema_tr_name_edit->text().isEmpty()) {
        enable = false;
    }
    ui->_save_as_btn->setEnabled(enable);
    ui->_save_btn->setEnabled(enable);
}

void ThemaBuilder_C::PopulateUI(Thema_C *thema)
{
    if(thema) {
        LOG_DEBUG("ThemaBuilder_C::PopulateUI");
        ui->_thema_name_edit->setText(thema->name());
        ui->_thema_tr_name_edit->setText(thema->trName());
        if(thema->author().isEmpty()) {
            ui->_author_name_edit->setText(UserName());
        } else {
            ui->_author_name_edit->setText(thema->author());
        }
        foreach(Word_C* word, thema->_words) {
            AddWordToList(word);
        }
        QDateTime thema_update_time = _thema->lastUpdated();
        if(thema_update_time.isValid()) {
            ui->_update_time_stamp_lbl->setText(thema_update_time.toString("dd-MM-yyyy hh:mm:ss"));
        } else {
            ui->_update_time_stamp_lbl->setText("");
        }

        if(_thema->lastPlayed().isValid()) {
            ui->_last_played_time_stamp_lbl->setText(_thema->lastPlayed().toString("dd-MM-yyyy hh:mm:ss"));
            ui->_last_played_date_time_edit->setDateTime(_thema->lastPlayed());
        } else {
            ui->_last_played_time_stamp_lbl->setText("NA");
        }
        ui->_points_edit->setText(QString::number(_thema->experiencePoints()));

        ui->_icon_lbl->setPixmap(_thema->_icon);
    }
}

void ThemaBuilder_C::SetWordUiState(ThemaBuilder_C::WordUIState new_state)
{
    if(new_state == ADD_STATE) {
        _edit_item = 0;
        ui->_add_btn->setText(tr("Add"));
        ui->_word_edit->setText("");
        ui->_desc_edit->setText("");
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

void ThemaBuilder_C::deleteItem(QListWidgetItem *item)
{
    if(item)
    {
        if(_edit_item == item) {
            SetWordUiState(ADD_STATE);
        }
        Word_C* word = item->data(WordListItem_C::WORD_ROLE).value<Word_C*>();
        if(word) {
            _thema->_words.removeAt(_thema->_words.indexOf(word));
            _word_item_hash.remove(word);
            _words_set.remove(wordId(word));
            delete word;
            delete item;
        }
    }
}

QString ThemaBuilder_C::UserName()
{
    QString user_name;
    user_name = qgetenv("USER");
    if(user_name.isEmpty()) {
        user_name = qgetenv("USERNAME");
    }
    if(user_name.isEmpty()) {
        user_name = "Anonymous Andy";
    }
    return user_name;
}

QString ThemaBuilder_C::lastPath(ThemaBuilder_C::PathType_TP path_type)
{
    QString path;
    QSettings settings;
    settings.beginGroup("pathSettings");
    switch(path_type)
    {
    case SAVE_PATH:
        path = settings.value("SAVE_PATH",QDir::homePath()).toString();
        break;
    case LOAD_PATH:
        path = settings.value("LOAD_PATH",QDir::homePath()).toString();
        break;
    case IMPORT_PATH:
        path = settings.value("IMPORT_PATH",QDir::homePath()).toString();
        break;
    case EXPORT_PATH:
        path = settings.value("EXPORT_PATH",QDir::homePath()).toString();
        break;
    case ICON_PATH:
        path = settings.value("ICON_PATH",QDir::homePath()).toString();
        break;
    case INDEX_PATH:
        path = settings.value("INDEX_PATH",QDir::homePath()).toString();
        break;
    case ICON_EXPORT_PATH:
        path = settings.value("ICON_EXPORT_PATH",QDir::homePath()).toString();
        break;
    default:
        break;
    }
    return path;
}

void ThemaBuilder_C::saveLastPath(ThemaBuilder_C::PathType_TP path_type, QString new_path)
{
    QSettings settings;
    settings.beginGroup("pathSettings");
    switch(path_type)
    {
    case SAVE_PATH:
        settings.setValue("SAVE_PATH",new_path);
        break;
    case LOAD_PATH:
        settings.setValue("LOAD_PATH",new_path);
        break;
    case IMPORT_PATH:
        settings.setValue("IMPORT_PATH",new_path);
        break;
    case EXPORT_PATH:
        settings.setValue("EXPORT_PATH",new_path);
        break;
    case ICON_PATH:
        settings.setValue("ICON_PATH",new_path);
        break;
    case INDEX_PATH:
        settings.setValue("INDEX_PATH",new_path);
        break;
    case ICON_EXPORT_PATH:
        settings.setValue("ICON_EXPORT_PATH",new_path);
        break;
    default:
        break;
    }
    settings.endGroup();
}

QString ThemaBuilder_C::wordId(Word_C *word)
{
    QString id;
    if(word) {
        id = QString("%1").arg(word->_text);
    }
    return id;
}
