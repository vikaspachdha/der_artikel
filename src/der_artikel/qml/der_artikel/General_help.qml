import QtQuick 2.1

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"To play the game select a thema from thema page and click start. \
\nUser shall land into words page with the words displayed on right side and \
articles on left side. \n\nTo gain points, user must assign articles to the nouns. Clicking on \
article button makes the corresponding article as selected article and clciking on words afterwards \
assigns the selected article to the clicked word. \n\nChange in word's background \
color confirms article assignment. The user must assign articles to all the words. \
Incorrect articles and unplayed words may result into points deduction depending \
on the gave level selected."

        wrapMode: Text.WordWrap
        font.family: custom_regular.name
        color:color_palette.color_font_01
        font.pixelSize: 16
    }
    contentHeight: content_text.contentHeight
}
