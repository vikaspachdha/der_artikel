import QtQuick 2.1

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:qsTr("To play the game select a thema from thema page and click start. \
\nwords page shall open with the words displayed on right side and \
articles on left side.\n\nTo gain points, user must assign correct articles to the nouns. \
Clicking on article button makes the corresponding article as active article and clicking \
on words afterwards assigns the selected article to the clicked word.\n\nChange in \
background color of word confirms article assignment. The user must assign articles \
to all the words. Incorrect articles and unplayed words may result into points deduction \
depending on the game level selected.")  + settings.i18n_empty_string

        wrapMode: Text.WordWrap
        font.family: regular_font.name
        color:color_palette.color_font_01
        font.pixelSize: normalTextSize
    }
    contentHeight: content_text.contentHeight
}
