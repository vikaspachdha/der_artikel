import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page_panel
{
    page_id:Manager.HOME_PAGE
    Label {
        id: home_lbl
        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: home_lbl.horizontalCenter
        lblText: qsTr("Home") + settings.i18n_empty_string
    }

    Column {
        id: home_btn_col
        anchors.top: home_lbl.bottom
        anchors.topMargin: 6
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.right: parent.right
        anchors.rightMargin: 4
        spacing: 6

        Button {
            id:rate_btn
            width:parent.width
            text_anchors.horizontalCenter: rate_btn.horizontalCenter
            buttonText: qsTr("Rate App") + settings.i18n_empty_string
            onActivated: showMessage(qsTr("Sorry"), qsTr("This feature is not available."),1200)
        }
    }

    Label {
        id:word_count_text_lbl
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        text_anchors.horizontalCenter: word_count_text_lbl.horizontalCenter
        lblText: qsTr("Total words") + settings.i18n_empty_string
    }

    Label {
        id:word_count_lbl
        property int words_count: themaModel.total_word_count
        anchors.top: word_count_text_lbl.bottom
        anchors.topMargin: -10
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_anchors.horizontalCenter: word_count_lbl.horizontalCenter
        textPxSize:heading1Size
        lblText: words_count
        Behavior on words_count {
            NumberAnimation { duration: 1000 }
        }
    }

}
