//******************************************************************************
/*! \file message_bar.cpp Implementation of \ref MessageBar_C
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
// System includes
#include <QQuickItem>
#include <QTimer>

// Interface for this file
#include "message_bar.h"
#include "settings.h"

// Framework and lib includes
#include "log4qt/log_defines.h"


//******************************************************************************
/*! \brief Construtor.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] parent : Parent object instance.
 ******************************************************************************/
MessageBar_C::MessageBar_C(QObject *parent) :
    QObject(parent)
{
    _message_loop = new QEventLoop(this);
    _close_loop = new QEventLoop(this);
    _min_duration_timer = new QTimer(this);
    _min_duration_timer->setSingleShot(true);
}

//******************************************************************************
/*! \brief Returns message bar instance.
 *
 *  \author Vikas Pachdha
 *
 *  \return MessageBar_C& : The message bar instance.
 ******************************************************************************/
MessageBar_C& MessageBar_C::instance()
{
    static MessageBar_C instance;
    return instance;
}

//******************************************************************************
/*! \brief Initializes the message bar.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] msg_bar : The message bar QML item.
 *  \param[in] settings : The settings instance.
 ******************************************************************************/
void MessageBar_C::init(QQuickItem *msg_bar, Settings_C* settings)
{
    _msg_bar = msg_bar;
    _settings = settings;
}

//******************************************************************************
/*! \brief Sets the accepted state of the message bar and closes the message bar.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] accepted : True to set accepted, false otherwise.
 ******************************************************************************/
void MessageBar_C::setAccepted(bool accepted)
{
    MessageBar_C& msg_bar_instance = instance();
    msg_bar_instance._accepted = accepted;
    closeMsg();
}

//******************************************************************************
/*! \brief Shows the message bar and it remains visible untill  either \ref
 *  MessageBar_C::closeMsg() is not called or user does not reponds using accept
 *  and reject button. Use the api to input the decision from user.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] accept_str : The accept button text. Default is "ok".
 *  \param[in] reject_str : The reject button text. Default is "Cancel".
 *  \param[in] type : Type of message bar.
 *
 *  \return MessageBar_C::RetrunType_TP Accepted state.
 *
 *  \see \ref MessageBar_C::MsgType_TP & MessageBar_C::RetrunType_TP
 ******************************************************************************/
MessageBar_C::RetrunType_TP MessageBar_C::showMsg(QString title, QString msg, QString accept_str, QString reject_str, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,-1),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,accept_str.isEmpty() ? QVariant() : accept_str),
                                  Q_ARG(QVariant,reject_str.isEmpty() ? QVariant() : reject_str));
        if(!msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->exec();
        }
    } else {
        LOG_ERROR("Message bar uninitialized usage");
    }
    return msg_bar_instance._accepted ? ACCEPTED : REJECTED;
}

//******************************************************************************
/*! \brief Shows the message bar with the given message and details. The message
 *  bar is automatic and closes after duration msecs.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] duration : The message bar closes after duration msecs.
 *  \param[in] type : Type of message bar.
 *
 *  \see \ref MessageBar_C::MsgType_TP
 ******************************************************************************/
void MessageBar_C::showMsg(QString title, QString msg, int duration, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QVariant null;
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,duration),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,null),
                                  Q_ARG(QVariant,null));
    } else {
        LOG_ERROR("Message bar uninitialized usage");
    }
}

//******************************************************************************
/*! \brief Shows the message bar and it remains visible untill \ref MessageBar_C::closeMsg()
 *  is not called. Use the api when a background task is to be performed restricting
 *  user interaction.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] title : The message headline.
 *  \param[in] msg : The message detail text.
 *  \param[in] min_duration : The minimum duration for which message is visible.
 *  \param[in] type : Type of message bar.
 *
 *  \see \ref MessageBar_C::MsgType_TP
 ******************************************************************************/
void MessageBar_C::showMsgAsync(QString title, QString msg, int min_duration, MessageBar_C::MsgType_TP type)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QVariant null;
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"showMessage",
                                  Q_ARG(QVariant,title),
                                  Q_ARG(QVariant,msg),
                                  Q_ARG(QVariant,-1),
                                  Q_ARG(QVariant,type),
                                  Q_ARG(QVariant,null),
                                  Q_ARG(QVariant,null));

        // Let the message bar show for some time.
        QTimer::singleShot(msg_bar_instance._settings->messageAnimTime() + 200,msg_bar_instance._message_loop,SLOT(quit()));
        if(!msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->exec();
        }

        if(min_duration > 0) {
            msg_bar_instance._min_duration_timer->stop();
            msg_bar_instance._min_duration_timer->setInterval(min_duration);
            msg_bar_instance._min_duration_timer->start();
        }

    } else {
        LOG_ERROR("Message bar uninitialized usage");
    }
}

//******************************************************************************
/*! \brief Updates the message string on message bar.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] msg : The message detail text.
 ******************************************************************************/
void MessageBar_C::setMessage(QString msg)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        msg_bar_instance._msg_bar->setProperty("message_txt",msg);
    } else {
        LOG_ERROR("Message bar uninitialized usage");
    }
}

//******************************************************************************
/*! \brief Updates the progress bar value on message bar.
 *
 *  \author Vikas Pachdha
 *
 *  \param[in] progress : Progress value. Should be between 0 and 1 where 1 is 100%.
 ******************************************************************************/
void MessageBar_C::setProgress(double progress)
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._msg_bar) {
        QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"setProgress",Q_ARG(QVariant,progress));
    } else {
        LOG_ERROR("Message bar uninitialized usage");
    }
}

//******************************************************************************
/*! \brief Closes the message bar. Method returns only when message bar is closed.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
void MessageBar_C::closeMsg()
{
    MessageBar_C& msg_bar_instance = instance();
    if(msg_bar_instance._min_duration_timer->isActive()) {
        QTimer::singleShot(msg_bar_instance._min_duration_timer->remainingTime(),&instance(),SLOT(closeMsg()));
    } else {
        if(msg_bar_instance._msg_bar) {
            // Let the message bar show for some time.
            QTimer::singleShot(500,msg_bar_instance._close_loop,SLOT(quit()));
            if(!msg_bar_instance._close_loop->isRunning()) {
                msg_bar_instance._close_loop->exec();
            }
            QMetaObject::invokeMethod(msg_bar_instance._msg_bar,"closeMessage");
        } else {
            LOG_ERROR("Message bar uninitialized usage");
        }

        // Don't return until message bar is hidden.
        QTimer::singleShot(msg_bar_instance._settings->messageAnimTime() + 100,msg_bar_instance._close_loop,SLOT(quit()));
        if(!msg_bar_instance._close_loop->isRunning()) {
            msg_bar_instance._close_loop->exec();
        }

        if(msg_bar_instance._message_loop->isRunning()) {
            msg_bar_instance._message_loop->quit();
        }
    }
}
