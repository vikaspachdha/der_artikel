#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QVector>
#include <QColor>
#include "common.h"

class QQuickItem;
class Thema_C;

class Manager_C : public QObject
{
    Q_OBJECT

    Q_PROPERTY(uint selected_article READ GetSelectedArticle WRITE SetSelectedArticle NOTIFY SelectedArticleChanged)
    Q_PROPERTY(QColor current_word_color READ GetCurrentWordColor)

public:
    explicit Manager_C(QObject *parent = 0);
    ~Manager_C();
    
public:
    void SetRootItem(QQuickItem* root_Item) { _root_item = root_Item; }

    void SetSelectedArticle(uint article);
    uint GetSelectedArticle() const { return (uint)_selected_article; }

    QColor GetCurrentWordColor() const { return _current_word_color; }

signals:
    void SelectedArticleChanged();
    
private slots:
    void OnNewThemaLoaded(Thema_C* new_thema);
    void OnSelectedArticleChanged();

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
    ARTIKEL::Artikel _selected_article;
    QColor _current_word_color;
};

#endif // MANAGER_H
