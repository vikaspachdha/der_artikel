#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>

class QQuickItem;
class Thema_C;

class Manager_C : public QObject
{
    Q_OBJECT
public:
    explicit Manager_C(QObject *parent = 0);
    ~Manager_C();
    
public:
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

signals:
    
public slots:
    void OnNewThemaLoaded(Thema_C* new_thema);

public:

// Helper methods
private:
    void LoadDefaultThemas();
    void SetCurrentThema(Thema_C* thema);
    void AddWords(const Thema_C *thema);
    QObject* AddWord(QString text);

private:
    QQuickItem* _root_item;
    QVector<Thema_C*> _themas;
    Thema_C* _current_thema;
};

#endif // MANAGER_H
