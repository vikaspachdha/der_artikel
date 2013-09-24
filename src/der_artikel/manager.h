#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
class QQuickItem;

class Manager_C : public QObject
{
    Q_OBJECT
public:
    explicit Manager_C(QObject *parent = 0);
    
public:
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

signals:
    
public slots:

// Helper methods
public:

    void AddWords();

private:

    QObject* AddWord(QString text);

private:

    QQuickItem* _root_item;
    
};

#endif // MANAGER_H
