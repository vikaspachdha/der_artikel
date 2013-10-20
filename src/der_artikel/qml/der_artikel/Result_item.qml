import QtQuick 2.0

Rectangle {
    id: rectangle1

    property alias item_title: text1.text
    property alias item_result: text2.text

    color: "#C7CDE6"
    width:parent.width
    //width: 300
    //height: 100
    Image {
        id: image1
        width: height
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        source: "qrc:/res/resources/save.png"
    }

    Text {
        id: text1
        height: parent.height*0.5
        font.pixelSize: height* 0.9
        smooth: true
        //anchors.right: parent.right
        anchors.rightMargin: 0
        verticalAlignment: Text.AlignVCenter
        anchors.left: image1.right
        anchors.leftMargin: 4
        anchors.top: parent.top
        anchors.topMargin: 0
    }

    Text {
        id: text2
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 4
        anchors.top: text1.bottom
        //anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: image1.right
        anchors.topMargin: 0
        font.pixelSize: height*0.9
        color:"green"
    }

//    states: [
//        State {
//            name: "landscape"
//            AnchorChanges { target: text1; anchors.bottom: rectangle1.bottom }
//        },
//        State {
//            name: "portrait"
//            AnchorChanges { target: text1; anchors.bottom: text2.bottom }
//        }
//    ]

//    transitions: Transition {
//        // smoothly reanchor myRect and move into new position
//        AnchorAnimation { duration: 200 }
//    }

//    onWidthChanged: {
//        var sum = text1.width + text2.width
//        console.log(width + " " + sum)
//        if(width > 900) {
//            console.log("Applied")
//            state="landscape"
//        } else {
//            state="portrait"
//        }
//    }

}
