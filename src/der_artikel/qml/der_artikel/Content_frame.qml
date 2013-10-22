import QtQuick 2.0

Item {
    id: root_item

    property Item current_page
    property Item next_page

    property alias word_page: words_page_item


    Words_page {
        id: words_page_item
        anchors.fill: parent
        visible:true
    }

    Thema_page {
        id: thema_page_item
        anchors.fill: parent
        visible:false
    }

    Result_page {
        id: result_page_item
        anchors.fill: parent
        visible:false
    }



//    states: [
//        State {
//            name: "show_online_devices"
//            AnchorChanges {
//                target:online_devices_list
//                anchors.top: title_rect.bottom
//                anchors.right: parent.right
//                anchors.bottom: parent.bottom
//                anchors.left: parent.left
//            }
//            AnchorChanges {
//                target:monitored_devices_list
//                anchors.top: title_rect.bottom
//                anchors.right: undefined
//                anchors.bottom: parent.bottom
//                anchors.left: parent.right
//            }
//            PropertyChanges {
//                target: title_text
//                text:qsTr("Online devices")
//            }

//        },
//        State {
//            name: "show_monitored_devices"
//            AnchorChanges {
//                target:monitored_devices_list
//                anchors.top: title_rect.bottom
//                anchors.right: parent.right
//                anchors.bottom: parent.bottom
//                anchors.left: parent.left
//            }
//            AnchorChanges {
//                target:online_devices_list
//                anchors.top: title_rect.bottom
//                anchors.right: undefined
//                anchors.bottom: parent.bottom
//                anchors.left: parent.right
//            }
//            PropertyChanges {
//                target: title_text
//                text:qsTr("Monitored devices")
//            }
//        }
//    ]

//    transitions: [
//        Transition {
//            from: "show_online_devices"
//            to: "show_monitored_devices"
//            reversible: true
//            AnchorAnimation { duration:400 }
//        }
//    ]



}
