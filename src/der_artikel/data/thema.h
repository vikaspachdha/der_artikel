#ifndef THEMA_H
#define THEMA_H
#include <QObject>
#include <QDomElement>
#include <QDateTime>
#include <QPixmap>
#include <QList>
#include <QUrl>
#include "word.h"
#include "thema_interface.h"

class QIODevice;


/**
 * @brief
 *
 */
class Thema_C : public QObject, public Thema_I
{

    Q_OBJECT

    Q_PROPERTY(bool selected READ Selected NOTIFY selectionChanged)
    Q_PROPERTY(int experience READ ExperiencePoints NOTIFY experiencePointsChanged)
    Q_PROPERTY(QString name READ GetText CONSTANT)
    Q_PROPERTY(QString tr_name READ GetTrText CONSTANT)
    Q_PROPERTY(unsigned int word_count READ GetWordCount CONSTANT)
    Q_PROPERTY(QDateTime last_played_date READ LastPlayed CONSTANT)
    Q_PROPERTY(State_TP state READ state NOTIFY stateChanged)

    Q_ENUMS(State_TP)
    Q_ENUMS(SelectionType_TP)

public:
    /**
     * @brief
     *
     */
    enum State_TP {
        RUSTY,
        SILVER,
        GOLD,
        INERT
    };

    /**
     * @brief
     *
     */
    enum SelectionType_TP {
        SINGLE_SELECTION,
        MULTI_SELECTION
    };

public:
/**
 * @brief
 *
 * @param parent
 */
    Thema_C(QObject* parent = 0);
    /**
     * @brief
     *
     */
    ~Thema_C();

public:

    /**
     * @brief
     *
     * @return QString
     */
    QString GetText() const { return _text; }

    /**
     * @brief
     *
     * @return QString
     */
    QString GetTrText() const { return _translation; }

    /**
     * @brief
     *
     * @return QString
     */
    QString Author() const { return _author; }

    /**
     * @brief
     *
     * @param file_path
     */
    void SetFilePath(QString file_path);

    /**
     * @brief
     *
     * @return QList<Word_C *>
     */
    QList<Word_C*> GetWords() const { return _words; }

    /**
     * @brief
     *
     * @return bool
     */
    bool Selected() const { return _selected; }
    /**
     * @brief
     *
     * @param selected
     * @param type
     */
    Q_INVOKABLE void setSelected(bool selected, SelectionType_TP type = SINGLE_SELECTION);

    /**
     * @brief
     *
     * @return const QPixmap
     */
    const QPixmap& GetIcon() const { return _icon; }

    /**
     * @brief
     *
     * @return int
     */
    int ExperiencePoints() const { return _experience_points; }

    /**
     * @brief
     *
     * @return QDateTime
     */
    QDateTime LastPlayed() const { return _last_played; }
    /**
     * @brief
     *
     * @param LastPlayed
     */
    void SetLastPlayed(const QDateTime &LastPlayed);

    /**
     * @brief
     *
     * @return State_TP
     */
    State_TP state() const { return _state; }

    // Thema_I implementation
public:
    /**
     * @brief
     *
     * @return unsigned int
     */
    virtual unsigned int GetWordCount() const;
    /**
     * @brief
     *
     * @param index
     * @return const Word_C
     */
    virtual const Word_C* GetWord(int index) const;
    /**
     * @brief
     *
     * @param points
     */
    virtual void AddExperiencePoints(int points);
    /**
     * @brief
     *
     * @param points
     */
    virtual void DeductExperiencePoints(int points);
    /**
     * @brief
     *
     */
    virtual void ClearUserInput();

public:
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Read(const QDomElement& element);
    /**
     * @brief
     *
     * @param element
     * @return bool
     */
    bool Write(QDomElement& element);
    /**
     * @brief
     *
     * @param file_path
     */
    void Save(QString file_path="");
    /**
     * @brief
     *
     */
    void ClearWords();


signals:
    /**
     * @brief
     *
     * @param Thema_C::SelectionType_TP
     */
    void selectionChanged(Thema_C::SelectionType_TP);
    /**
     * @brief
     *
     */
    void experiencePointsChanged();
    /**
     * @brief
     *
     */
    void stateChanged();

private:
    /**
     * @brief
     *
     * @param pDevice
     * @return bool
     */
    bool Write(QIODevice* pDevice);
    /**
     * @brief
     *
     */
    void UpdateThemaState();
    /**
     * @brief
     *
     * @return QByteArray
     */
    QByteArray IconData() const;
    /**
     * @brief
     *
     * @param data
     */
    void UpdateIcon(QByteArray data);

private:
    QString _text; /**< TODO */
    QString _translation; /**< TODO */
    QString _author; /**< TODO */
    QString _file_path; /**< TODO */
    QList<Word_C*> _words; /**< TODO */
    bool _defered_read; /**< TODO */
    QDateTime _last_played; /**< TODO */
    int _experience_points; /**< TODO */
    bool _selected; /**< TODO */
    QPixmap _icon; /**< TODO */
    State_TP _state; /**< TODO */

private:
    friend class ThemaBuilder_C;
};

Q_DECLARE_METATYPE(Thema_C::SelectionType_TP)

#endif // THEMA_H
