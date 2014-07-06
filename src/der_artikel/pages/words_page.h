//******************************************************************************
/*! \file words_page.h Declaration of \ref WordsPage_C
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
#ifndef WORDS_PAGE_H
#define WORDS_PAGE_H

// System includes
#include <QColor>
#include <QHash>

// Framework and lib includes
#include "data/article.h"

// Project includes
#include "page.h"

// Forward declaration
class Word_C;
class Settings_C;

//******************************************************************************
/*! \brief Entity class for words page. The entity defines menu items for the
 *  words page and how to use the shared user interface elements such as menu and
 *  status bar.
 *
 *  \details User is provided with user interface to play the selected thema.
 *
 *  \author Vikas Pachdha
 ******************************************************************************/
class WordsPage_C : public Page_C
{
    Q_OBJECT
    Q_PROPERTY(bool info_mode READ infoMode WRITE setInfoMode NOTIFY infoModeChanged)
    Q_PROPERTY(Article_C::Artikel selected_article READ getSelectedArticle WRITE setSelectedArticle NOTIFY selectedArticleChanged)
    Q_PROPERTY(QString word_description READ wordDescription NOTIFY wordDescriptionChanged)
public:
    explicit WordsPage_C(Manager_C& page_manager, QQmlContext& root_context, Settings_C& settings, QObject *parent = 0);
    ~WordsPage_C();

public:
    virtual bool canEnter() const;
    virtual void enter(Manager_C::PageId_TP prev_page_id);
    virtual void leave(Manager_C::PageId_TP next_page_id);

public:
    //! Returns true if info mode is active, false otherwise.
    bool infoMode() const { return _info_mode; }
    void setInfoMode(bool info_mode);

    void setSelectedArticle(Article_C::Artikel article);
    //! Returns selected artikel.
    Article_C::Artikel getSelectedArticle() const { return _selected_article; }

    //! Returns last selected word's description.
    QString wordDescription() const { return _current_word_description; }

private slots:
    void onWordClicked();
    void calculateExperienceLoss();

signals:
    //! Emitted when info mode is changed.
    void infoModeChanged();
    //! Emitted when selected article is changed.
    void selectedArticleChanged();
    //! Emitted when desription text changes.
    void wordDescriptionChanged();

private:
    void addWords(const Thema_C *thema, bool practice_mode=false);
    QObject* addWord(Word_C &word);
    void clearWordItems();
    void createResultAlgo();
    void calculateResult();
    void updateWordDescription(const Word_C* word);

private:
    //! Root QML context instance.
    QQmlContext& _root_context;
    //! Settings instance.
    Settings_C& _settings;
    //! True if info mode is selected.
    bool _info_mode;
    //! QML word item and \ref Word_C associations.
    QHash<QObject*, Word_C*> _item_word_hash;
    //! Selected Article.
    Article_C::Artikel _selected_article;
    //! Result algorithm instance.
    ResultAlgo_I* _result_algo;
    //! Last selected word's description.
    QString _current_word_description;
};

#endif // WORDS_PAGE_H
