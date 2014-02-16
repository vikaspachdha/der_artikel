#ifndef THEMA_BUILDER_H
#define THEMA_BUILDER_H



#ifdef ENABLE_THEMA_BUILDER

#include <QWidget>
#include <QHash>
#include <QTimer>

class Thema_C;

namespace Ui {
class ThemaBuilder_C;
}
class QIODevice;
class QAbstractButton;
class QListWidgetItem;
class Word_C;
class QKeyEvent;

class ThemaBuilder_C : public QWidget
{
    Q_OBJECT

enum WordUIState {
    ADD_STATE,
    UPDATE_STATE
};

public:
    explicit ThemaBuilder_C(QWidget *parent = 0);
    ~ThemaBuilder_C();

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);

private slots:
    void OnDlgButtonClicked(QAbstractButton* btn);
    void OnNew();
    void OnLoad();
    void OnSave();
    void OnSaveAs();
    void OnExport();
    void OnIcon();
    void OnImport();
    void OnAddClicked();
    void OnWordTextChanged(QString new_text);
    void OnThemaNameChanged(QString new_text);
    void OnItemDoubleClicked(QListWidgetItem *item);
    void OnWordSelectionChanged();
    void OnDelete();

    void InsertAUmlaut();
    void InsertOUmlaut();
    void InsertUUmlaut();
    void InsertEszett();

    void onEnableDateTimeChk(bool enabled);
    void onUpdateTime();

private:
    void UpdateItem(QListWidgetItem* item);
    bool Save(QString save_file);
    bool Write(QIODevice* pDevice);
    bool Export(QIODevice* pDevice);
    bool Import(QIODevice* pDevice);
    bool AddWordToList(Word_C *new_word);
    bool AddWordToThema(Word_C *new_word);
    void Reset();
    void UpdateUI();
    void PopulateUI(Thema_C* thema);
    void SetWordUiState(WordUIState new_state);
    void InsertSplText(QString str);
    void SetUmlautUpperCase( bool upper_case);
    QString UserName();

private:
    Ui::ThemaBuilder_C *ui;
    Thema_C* _thema;
    QHash<QString, Word_C*> _words_set;
    QHash<Word_C*, QListWidgetItem*> _word_item_hash;
    QListWidgetItem* _edit_item;
    QTimer _date_time_timer;
};
#endif // ENABLE_THEMA_BUILDER

#endif // THEMA_BUILDER_H
