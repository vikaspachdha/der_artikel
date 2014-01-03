import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {
    page_id: Manager.RESULT_PAGE
    Text {
        id: heading_1
        text:currentResult.grade_string
        anchors {
            top:parent.top
            left:parent.left
            leftMargin: 6
            topMargin: 6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_1_right
        text:currentResult.unplayed_string
        anchors {
            top:parent.top
            right:parent.right
            rightMargin:6
            topMargin: 6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 14
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_2
        text:currentResult.score_string
        anchors {
            top:heading_1.bottom
            topMargin: 6
            left:parent.left
            leftMargin: 6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_2_right
        text: currentResult.mistake_string

        anchors {
            top:heading_1_right.bottom
            topMargin: 6
            right:parent.right
            rightMargin:6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 14
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_3_right
        text: {
            if(currentResult.experience_change<0) {
                return qsTr("Lost experience : " + -1*currentResult.experience_change)
            } else {
                return qsTr("Gained experience : " + currentResult.experience_change)
            }
        }

        anchors {
            top:heading_2_right.bottom
            topMargin: 6
            right:parent.right
            rightMargin:6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 14
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }
}
