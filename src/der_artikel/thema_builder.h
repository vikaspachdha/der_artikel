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

class ThemaBuilder_C : public QWidget
{
    Q_OBJECT

public:
    explicit ThemaBuilder_C(QWidget *parent = 0);
    ~ThemaBuilder_C();

private slots:
    void OnDlgButtonClicked(QAbstractButton* btn);
    void OnAddClicked();
    void OnWordTextChanged(QString new_text);
    void OnThemaNameChanged(QString new_text);
    void OnItemDoubleClicked(QListWidgetItem *item);

private:
    void OnSave();
    bool Write(QIODevice* pDevice);
private:
    Ui::ThemaBuilder_C *ui;
    Thema_C* _thema;
};

#endif // THEMA_BUILDER_H
