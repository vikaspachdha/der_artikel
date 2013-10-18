import QtQuick 2.0

Rectangle {
    id: rectangle1

    //anchors.fill: parent

    width: 800
    height: 600

    Rectangle {
        id: title_rect
        height: parent.height * 0.1
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
        color: "#ABB5DA"

        Text {
            id: title_text
            anchors.fill: parent
            text: qsTr("Result")
            font.pixelSize: height * 0.8
            horizontalAlignment: Text.AlignHCenter
        }
    }

    ListView {
        id: list_view1

        anchors.top: title_rect.bottom
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing:4
        clip:true
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
        delegate: Result_item {

            height: 20
            item_title: model.name
            item_result: model.colorCode
        }
    }


}
