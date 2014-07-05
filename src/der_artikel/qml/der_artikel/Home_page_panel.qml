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
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Home") + settings.i18n_empty_string
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
            text_h_alignment: Text.AlignHCenter
            buttonText: qsTr("Rate App") + settings.i18n_empty_string
            onActivated: {
                Qt.openUrlExternally("https://www.facebook.com/der.artikel")
            }
        }
    }

    Label {
        id:word_count_text_lbl
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        anchors.verticalCenter: parent.verticalCenter
        text_h_alignment: Text.AlignHCenter
        text: qsTr("Total words") + settings.i18n_empty_string
    }

    Label {
        id:word_count_lbl
        property int words_count: themaModel.total_word_count
        anchors.top: word_count_text_lbl.bottom
        anchors.left: parent.left
        anchors.leftMargin: 2
        anchors.right: parent.right
        anchors.rightMargin: 2
        text_h_alignment: Text.AlignHCenter
        text_px_size:heading1Size
        text: words_count
        Behavior on words_count {
            NumberAnimation { duration: 1000 }
        }
    }

}
