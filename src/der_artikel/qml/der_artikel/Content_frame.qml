import QtQuick 2.0

Item {
    id: root_item

    property Item current_page
    property Item next_page

    property alias word_page: words_page_item


    Home_page {
        id: home_page_item
        anchors.top: root_item.top
        anchors.right: undefined
        anchors.bottom: root_item.bottom
        anchors.left: root_item.right
    }

    Words_page {
        id: words_page_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        //visible: false

    }

    Thema_page {
        id: thema_page_item
        anchors.top: root_item.top
        anchors.right: undefined
        anchors.bottom: root_item.bottom
        anchors.left: root_item.right
    }

    Result_page {
        id: result_page_item
        anchors.top: root_item.top
        anchors.right: undefined
        anchors.bottom: root_item.bottom
        anchors.left: root_item.right
    }



    states: [
        State {
            name: "slide_in"
            AnchorChanges {
                target:next_page
                anchors.top: root_item.top
                anchors.right: root_item.right
                anchors.bottom: root_item.bottom
                anchors.left: root_item.left
            }
            AnchorChanges {
                target:current_page
                anchors.top: root_item.top
                anchors.right: undefined
                anchors.bottom: root_item.bottom
                anchors.left: root_item.right
            }

        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "slide_in"
            reversible: true
            AnchorAnimation {
                duration:1000
                onRunningChanged: {
                    if(running==false) {
                        root_item.state=""
                    }
                }
            }
        }
    ]

Component.onCompleted: {
    current_page = words_page_item
}

function showThemaPage()
{
    next_page=thema_page_item
    state="slide_in"
}

}
