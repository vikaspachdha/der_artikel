#ifndef THEMA_BUILDER_H
#define THEMA_BUILDER_H

#include <QWidget>

namespace Ui {
class ThemaBuilder_C;
}
class QIODevice;
class QAbstractButton;

class ThemaBuilder_C : public QWidget
{
    Q_OBJECT

public:
    explicit ThemaBuilder_C(QWidget *parent = 0);
    ~ThemaBuilder_C();

private slots:
    void OnDlgButtonClicked(QAbstractButton* btn);

private:
    void OnSave();
    bool Write(QIODevice* pDevice);
private:
    Ui::ThemaBuilder_C *ui;
};

#endif // THEMA_BUILDER_H
