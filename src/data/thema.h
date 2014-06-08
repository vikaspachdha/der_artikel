//******************************************************************************
/*! \file thema.h Declaration of \ref Thema_C
 *
 *  \author Vikas Pachdha
 *
 *  \copyright Copyright (C) 2014 Vikas Pachdha, Mohita Gandotra.
 * Contact: http://www.vikaspachdha.com
 *
 * This file is part of the application der_artikel.
 *
 *  \copyright GNU Lesser General Public License Usage
 * This file may be used under the terms of the GNU Lesser
 * General Public License version 2.1 as published by the Free Software
 * Foundation and appearing in the file LICENSE.LGPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU Lesser General Public License version 2.1 requirements
 * will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 *
 *  \copyright GNU General Public License Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 *
 ******************************************************************************/
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

//******************************************************************************
/*! \brief Data class defining a thema.
 *
 *  \details The \ref Word_C "words" loading can be defered to save memory.
 *
 *  \author Vikas Pachdha
 *
 *  \see \ref ThemaLoader_C
 ******************************************************************************/
class Thema_C : public QObject, public Thema_I
{
    Q_OBJECT

    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectionChanged)
    Q_PROPERTY(int experience READ experiencePoints NOTIFY experiencePointsChanged)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString tr_name READ trName CONSTANT)
    Q_PROPERTY(unsigned int word_count READ wordCount CONSTANT)
    Q_PROPERTY(QDateTime last_played_date READ lastPlayed CONSTANT)
    Q_PROPERTY(State_TP state READ state NOTIFY stateChanged)

    Q_ENUMS(State_TP)
    Q_ENUMS(SelectionType_TP)

public:
    //******************************************************************************
    /*! \brief Thema state.
     *
     *  \details A thema attains a state as per the experience gained.
     *
     *  \author Vikas Pachdha
     ******************************************************************************/
    enum State_TP {
        RUSTY,
        SILVER,
        GOLD,
        INERT
    };

public:
    Thema_C(QObject* parent = 0);
    ~Thema_C();

public:

    //! Returns name of the thema.
    QString name() const { return _text; }

    //! Returns translated name of the thema.
    QString trName() const { return _translation; }

    //! returns Author of the thema.
    QString author() const { return _author; }

    //! Returns complete file path of the thema.
    QString filePath() const { return _file_path; }

    //! Returns list of words of the thema.
    QList<Word_C*> words() const { return _words; }

    //! Returns true in case thema is in selected state, false otherwise.
    bool selected() const { return _selected; }

    void setSelected(bool selected);

    //! Return thema icon.
    const QPixmap& themaIcon() const { return _icon; }

    //! Return experience points.
    int experiencePoints() const { return _experience_points; }

    //! Returns date and time of thema when its was last played.
    QDateTime lastPlayed() const { return _last_played; }
    void setLastPlayed(const QDateTime &Last_played);

    //! Returns date and time of thema when it was last updated.
    QDateTime lastUpdated() const { return _last_updated; }
    void setLastUpdated(const QDateTime &last_updated);

    //! Returns \ref State_TP state of the thema.
    State_TP state() const { return _state; }

    // Thema_I implementation
public:
    virtual unsigned int wordCount() const;
    virtual const Word_C* word(int index) const;
    virtual void addExperiencePoints(int points);
    virtual void deductExperiencePoints(int points);
    virtual void clearUserInput();

public:
    bool read(QString thema_file_path, bool defered = true);
    bool write(QDomElement& element);
    bool save(QString file_path="");
    void clearWords();

signals:
    //! Emitted when selection state changes.
    void selectionChanged();
    //! Emitted when experiene points are changed for this thema.
    void experiencePointsChanged();
    //! Emitted when state of this thema changes.
    void stateChanged();

private:
    bool read(const QDomElement& element, bool defered=true);
    bool write(QIODevice* pDevice);
    void updateThemaState();
    QByteArray iconData() const;
    void updateIcon(QByteArray data);
    void resetThema();

private:
    QString _text;
    QString _translation;
    QString _author;
    QString _file_path;
    QList<Word_C*> _words;
    QDateTime _last_played;
    QDateTime _last_updated;
    int _experience_points;
    bool _selected;
    QPixmap _icon;
    State_TP _state;

private:
    friend class ThemaBuilder_C;
    friend class ResultAlgo_T;
    friend class FileOperationAlgo_T;
};
#endif // THEMA_H
