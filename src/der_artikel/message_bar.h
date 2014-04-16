//******************************************************************************
/*! \file manager.h Declaration of \ref Manager_C
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
#ifndef MESSAGE_BAR_H
#define MESSAGE_BAR_H

// System includes
#include <QObject>
#include <QEventLoop>

// Forward declarations
class QQuickItem;
class Settings_C;

//******************************************************************************
/*! \brief Provides access to QML message bar..
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class MessageBar_C : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MessageBar_C)
    Q_ENUMS(MsgType_TP)
    Q_ENUMS(RetrunType_TP)
public:
    //! Message bar type.
    //! <ul>
    //! <li> INFO : Information message bar. </li>
    //! <li> WARNING : Warning message bar. </li>
    //! <li> ERROR : Error message bar. </li>
    //! </ul>
    enum MsgType_TP
    {
        INFO = 1,
        WARNING,
        ERROR,
    };

    //! Message bar accepted states.
    //! <ul>
    //! <li> ACCEPTED : Message bar is accepted. </li>
    //! <li> REJECTED : Message bar is rejected. </li>
    //! </ul>
    enum RetrunType_TP
    {
        ACCEPTED,
        REJECTED
    };

private:
    explicit MessageBar_C(QObject *parent = 0);

public:

    static MessageBar_C& instance();

    void init(QQuickItem* msg_bar, Settings_C *settings);

    Q_INVOKABLE void setAccepted(bool accepted);

    static RetrunType_TP showMsg(QString title, QString msg,
                                     QString accept_str = tr("Ok"),
                                     QString reject_str = tr("Cancel"),
                                     MsgType_TP type = INFO);

    static void showMsg(QString title, QString msg,
                            int duration,
                            MsgType_TP type = INFO);

    static void showMsgAsync(QString title, QString msg,
                                 MsgType_TP type = INFO);

    static void closeMsg();

private:
    //! Event loop for message bar.
    QEventLoop _message_loop;

    //! Message bar QML item
    QQuickItem* _msg_bar;

    //! Application settings
    Settings_C* _settings;

    //! Accepted state.
    bool _accepted;
};

#endif // MESSAGE_BAR_H
