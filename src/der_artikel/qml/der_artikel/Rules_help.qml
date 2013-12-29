import QtQuick 2.0

Flickable {
    anchors.fill: parent
    anchors.margins: 4
    Text {
        id: content_text
        anchors.fill: parent
        text:"1. Correct article gains experience points.<br><br>2. Incorrect article shall \
result into experience points deduction. Magnitude of the deduction shall depend on the \
game level selected for gamplay.<br><br>3. Unplayed words may \
result into experience points deduction. Magnitude of the deduction shall depend on the \
game level selected for gamplay.<br><br>4. Gaining points changes the state of the thema. \
<table border=\"1\">
<tr>
<td><b>Experience</b></td>
<td><b>State</b></td>
</tr>
<tr>
<td>&lt;100</td>
<td>RUSTY</td>
</tr>
<tr>
<td>&gt;100 & &lt;250</td>
<td>SILVER</td>
</tr>
<tr>
<td>&gt;250 & &lt;500</td>
<td>GOLD</td>
</tr>
<tr>
<td>&gt;500</td>
<td>INERT</td>
</tr>
</table> \
<br><br>5. A thema shall lose 10 points if experinece points gain does not occue within 24 hrs \
and this rule shall be applicaple until thema reaches INERT state. So keep playing a thema \
untill you reach the INERT state."

        wrapMode: Text.WordWrap
        font.family: custom_regular.name
        color:cp_blue.colorf02
        font.pixelSize: 16
        textFormat: Text.RichText
    }
    contentHeight: content_text.contentHeight
}
