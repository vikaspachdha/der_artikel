#ifndef THEMA_LOADER_H
#define THEMA_LOADER_H

#include <QObject>
#include <QString>
#include <QRunnable>

class Thema_C;

/**
 * @brief
 *
 */
class ThemaLoader_C: public QObject, public QRunnable
{
    Q_OBJECT
public:
/**
 * @brief
 *
 * @param thema_parent
 * @param parent
 */
    ThemaLoader_C(QObject* thema_parent=0, QObject* parent = 0);

protected:
    /**
     * @brief
     *
     */
    virtual void run();

public:
    /**
     * @brief
     *
     * @param file_path
     * @return Thema_C
     */
    Thema_C* LoadThema(QString file_path);
    /**
     * @brief
     *
     */
    void StartLoading();

signals:
    /**
     * @brief
     *
     * @param new_thema
     */
    void ThemaLoaded(Thema_C* new_thema);

private:

    QString _root_dir; /**< TODO */
    QObject* _thema_parent; /**< TODO */
};

#endif // THEMA_LOADER_H
