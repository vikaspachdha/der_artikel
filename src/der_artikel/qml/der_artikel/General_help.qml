import QtQuick 2.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"To play the game select a thema from thema page and click start. \
User shall land into words page with the words displayed on right side and \
articles on left side. User must assign articles to the nouns. Clicking on \
Article button makes it the selected article and clciking on words afterwards \
assigns the selected article to the clocked word. Change in word's background \
color confirms article assignment. The user must assign articles to all the words. \
Incorrect articles and unplayed words may result into points deduction depending \
on the gave level selected."

        wrapMode: Text.WordWrap
        font.family: custom_regular.name
        color:cp_blue.colorf02
        font.pixelSize: 16
    }
    contentHeight: content_text.contentHeight
}
