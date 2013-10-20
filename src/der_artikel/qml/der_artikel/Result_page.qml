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
            fontSizeMode: Text.Fit
        }
    }

    ListView {
        id: list_view1

        anchors.top: rectangle3.bottom
        anchors.topMargin: 4
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing:4
        clip:true
        model: ListModel {
            ListElement {
                incorrect_word: "Die Bruder"
                correct_word: "Der Bruder"
            }
            ListElement {
                incorrect_word: "Die Bruder"
                correct_word: "Der Bruder"
            }
            ListElement {
                incorrect_word: "Die Bruder"
                correct_word: "Der Bruder"
            }
            ListElement {
                incorrect_word: "Die Bruder"
                correct_word: "Der Bruder"
            }
            ListElement {
                incorrect_word: "Die Bruder"
                correct_word: "Der Bruder"
            }


        }
        delegate: Result_item {

            height: 20
            item_title: model.incorrect_word
            item_result: model.correct_word
        }
    }

    Rectangle {
        id: rectangle2
        height: parent.height * 0.1
        color: "#abb5da"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: title_rect.bottom
        anchors.topMargin: 4

        Text {
            id: score_text
            anchors.fill: parent
            text: qsTr("80% Accuracy")
            font.pixelSize: height * 0.8
            horizontalAlignment: Text.AlignHCenter
            fontSizeMode: Text.Fit
        }
    }

    Rectangle {
        id: rectangle3
        height: parent.height*0.05
        color: "#abb5da"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: rectangle2.bottom
        anchors.topMargin: 4

        Text {
            id: title_word_list
            anchors.fill: parent
            text: qsTr("Mistakes")
            font.pixelSize: height * 0.8
            horizontalAlignment: Text.AlignHCenter
            fontSizeMode: Text.Fit
        }
    }


}
