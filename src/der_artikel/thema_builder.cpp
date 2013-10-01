#include "thema_builder.h"
#include "ui_thema_builder.h"

#include <QDomDocument>
#include <QFileDialog>
#include <QFile>
#include <QDebug>

#include "data/thema.h"

ThemaBuilder_C::ThemaBuilder_C(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemaBuilder_C)
{
    ui->setupUi(this);
    connect(ui->_btn_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(OnDlgButtonClicked(QAbstractButton*)) );
}

ThemaBuilder_C::~ThemaBuilder_C()
{
    delete ui;
}

void ThemaBuilder_C::OnDlgButtonClicked(QAbstractButton *btn)
{
    if(ui->_btn_box->standardButton(btn) == QDialogButtonBox::Save) {
        OnSave();
    } else {
        close();
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

    QDomDocument domDocument("DerArtikel");

    QTextStream out(pDevice);
    QDomElement root = domDocument.createElement("Root");
    root.setAttribute("Version", "1.0");


    Thema_C thema;
    thema.SetText(ui->_thema_name_edit->text().trimmed());
    thema.SetTrText(ui->_theam_tr_name_edit->text().trimmed());
    thema.Write(root);

    domDocument.appendChild(root);
    domDocument.save(out, 4);

    return true;
}
