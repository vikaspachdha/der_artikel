#include "thema_loader.h"

#include <QDomDocument>
#include <QFile>
#include <QMessageBox>
#include <QDebug>

#include "version.h"
#include "data/thema.h"

ThemaLoader_C::ThemaLoader_C(QObject *parent) : QObject(parent)
{
}

Thema_C *ThemaLoader_C::LoadThema(QString file_path)
{
    Thema_C* thema = 0;
    QFile thema_file(file_path);

    if(thema_file.open(QFile::ReadOnly)) {
        QDomDocument thema_doc;
        QString error_msg;
        int error_line;
        int error_col;
        if(thema_doc.setContent(&thema_file, &error_msg, &error_line, &error_col)) {
            //parse the file and read the thema.
            QDomElement root = thema_doc.firstChildElement("DerArtikel");
            QDomAttr versionAttr = root.attributeNode("Version");
            QString versionStr = versionAttr.value();

            bool ok = false;
            int version = versionStr.toInt(&ok);
            if(ok) {
                if(version <= APP_VERSION) {

                    QDomNode domNode = root.firstChild();
                    while (!domNode.isNull()) {
                        if(domNode.nodeName().compare("Thema") == 0) {
                            thema = new Thema_C();
                            if(!thema->Read(domNode.toElement())) {
                                delete thema;
                                thema = 0;
                            }
                        }
                    }

                } else {
                    qDebug()<<"Cannot parse thema file. This version is not supported : "<<version;
                    QMessageBox::critical(0, tr("Invalid thema file version."), tr("Cannot parse thema file. This version is not supported : %1.").arg(version));
                }
            }
        } else {
            qDebug()<<"Invalid thema file. "<<error_msg<<" Line : "<<error_line<<" Col: "<<error_col;
            QMessageBox::critical(0, tr("Invalid thema file."), tr("Cannot parse thema file. Check logs for futher details."));
        }

    } else {
        qDebug()<<thema_file.errorString();
    }

    return thema;
}
