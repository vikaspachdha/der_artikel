#ifndef THEMA_BUILDER_H
#define THEMA_BUILDER_H

#include <QWidget>

class Thema_C;

namespace Ui {
class ThemaBuilder_C;
}
class QIODevice;
class QAbstractButton;
class QListWidgetItem;
class Word_C;

class ThemaBuilder_C : public QWidget
{
    Q_OBJECT

public:
    explicit ThemaBuilder_C(QWidget *parent = 0);
    ~ThemaBuilder_C();

private slots:
    void OnDlgButtonClicked(QAbstractButton* btn);
    void OnLoad();
    void OnSave();
    void OnAddClicked();
    void OnWordTextChanged(QString new_text);
    void OnThemaNameChanged(QString new_text);
    void OnItemDoubleClicked(QListWidgetItem *item);
    void OnWordSelectionChanged();
    void OnDelete();

private:
    bool Write(QIODevice* pDevice);
    void AddWordToList(Word_C *new_word);
    void ResetUI();
    void PopulateUI(Thema_C* thema);

private:
    Ui::ThemaBuilder_C *ui;
    Thema_C* _thema;
};

#endif // THEMA_BUILDER_H
