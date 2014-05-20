import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.THEMA_PAGE

    GridView {
        id: grid_view
        anchors.rightMargin: 4
        anchors.leftMargin: 4
        anchors.bottomMargin: 4
        anchors.topMargin: 4
        anchors.fill: parent
        model: themaModel
        cellHeight: 110
        cellWidth: 110
        delegate: Thema_item {
            title:display_name
            translation: tr_name
            author_name: author
            last_played_text:Qt.formatDateTime(last_played,"dd.MM.yy - hh:mm")+ qsTr(" hrs") +settings.i18n_empty_string
            icon_url: "image://rootImageProvider/"+display_name
            count:word_count
            width:grid_view.cellWidth-4
            height:grid_view.cellHeight-4
            thema_selected: selected
            onThemaClicked: {
                if(flipped) {
                    flipped = !flipped
                }else {
                    themaModel.clearSelection()
                    thema_object.selected = !thema_object.selected
                }
            }
            onThemaLongClicked: {
                thema_object.selected = true;
            }
        }
    }
}
