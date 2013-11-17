import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {

    GridView {
        id: grid_view
        anchors.rightMargin: 4
        anchors.leftMargin: 4
        anchors.bottomMargin: 4
        anchors.topMargin: 4
        anchors.fill: parent
        model: manager.thema_model
        cellHeight: 120
        cellWidth: 120
        delegate: Thema_item {
            title:display_name
            translation: tr_name
            icon_url: icon
            count:word_count
            width:grid_view.cellHeight
            height:grid_view.cellHeight
        }
    }
}
