import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    //anchors.fill: parent

    //width: 800
    //height: 600

    GridView {
        id: grid_view1
        anchors.rightMargin: 4
        anchors.leftMargin: 4
        anchors.bottomMargin: 4
        anchors.topMargin: 4
        anchors.fill: parent
        model: manager.thema_model
        cellHeight: 48
        delegate: Item {
            x: 5
            height: 50
            Column {
                Rectangle {
                    width: 40
                    height: 40
                    color: "green"
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Text {
                    x: 5
                    text: tr_name
                    font.bold: true
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                spacing: 5
            }
        }
        cellWidth: 32
    }
}
