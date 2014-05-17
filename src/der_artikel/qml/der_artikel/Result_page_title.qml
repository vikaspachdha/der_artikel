import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Title_bar {
    page_id: Manager.RESULT_PAGE
    Text {
        id: heading_1
        text:currentResult.grade_string + settings.i18n_empty_string
        anchors {
            top:parent.top
            left:parent.left
            leftMargin: 6
            topMargin: 6
        }
        color: color_palette.color_font_01
        font.family: title_font.name
        font.pixelSize: heading1Size
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_1_right
        text:currentResult.unplayed_string + settings.i18n_empty_string
        anchors {
            top:parent.top
            right:parent.right
            rightMargin:6
            topMargin: 6
        }
        color: color_palette.color_font_01
        font.family: title_font.name
        font.pixelSize: heading2Size
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_2
        text:currentResult.score_string + settings.i18n_empty_string
        anchors {
            top:heading_1.bottom
            topMargin: 6
            left:parent.left
            leftMargin: 6
        }
        color: color_palette.color_font_01
        font.family: title_font.name
        font.pixelSize: heading1Size
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_2_right
        text: currentResult.mistake_string + settings.i18n_empty_string

        anchors {
            top:heading_1_right.bottom
            topMargin: 6
            right:parent.right
            rightMargin:6
        }
        color: color_palette.color_font_01
        font.family: title_font.name
        font.pixelSize: heading2Size
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_3_right
        text: {
            if(currentResult.experience_change<0) {
                return qsTr("Lost experience : ") + -1*currentResult.experience_change + settings.i18n_empty_string
            } else {
                return qsTr("Gained experience : ") + currentResult.experience_change + settings.i18n_empty_string
            }
        }

        anchors {
            top:heading_2_right.bottom
            topMargin: 6
            right:parent.right
            rightMargin:6
        }
        color: color_palette.color_font_01
        font.family: title_font.name
        font.pixelSize: heading2Size
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }
}
