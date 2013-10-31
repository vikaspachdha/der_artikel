import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: root_item

    property Item current_page
    property Item next_page

    property alias word_page: words_page_item
    clip:true

    Home_page {
        id: home_page_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible: true
    }

    Words_page {
        id: words_page_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible: false
    }

    Thema_page {
        id: thema_page_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible: false
    }

    Result_page {
        id: result_page_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible: false
    }

    About_page {
       id: about_page_item
       anchors.top: root_item.top
       anchors.right: root_item.right
       anchors.bottom: root_item.bottom
       anchors.left: root_item.left
       anchors.margins: 4
       visible: false
    }



//    states: [
//        State {
//            name: ""
//            AnchorChanges {
//                target:next_page
//                anchors.top: root_item.top
//                anchors.right: root_item.right
//                anchors.bottom: root_item.bottom
//                anchors.left: root_item.left
//            }
//            AnchorChanges {
//                target:current_page
//                anchors.top: root_item.top
//                anchors.right: undefined
//                anchors.bottom: root_item.bottom
//                anchors.left: root_item.right
//            }

//        },
//        State {
//            name: "slide_in"
//            AnchorChanges {
//                target:next_page
//                anchors.top: root_item.top
//                anchors.right: root_item.right
//                anchors.bottom: root_item.bottom
//                anchors.left: root_item.left
//            }
//            AnchorChanges {
//                target:current_page
//                anchors.top: root_item.top
//                anchors.right: undefined
//                anchors.bottom: root_item.bottom
//                anchors.left: root_item.right
//            }

//        }
//    ]

//    transitions: [
//        Transition {
//            id:trans
//            from: ""
//            to: "slide_in"
//            reversible: true
//            AnchorAnimation {
//                duration:400
//                easing.type: Easing.OutExpo
//            }
//            onRunningChanged: {
//                if(running==false) {
//                    current_page=next_page
//                    console.log(current_page)
//                }
//            }
//        }
//    ]

Component.onCompleted: {
    current_page = home_page_item
    manager.currentPageChanged.connect(onCurrenPageChanged)
}


function onCurrenPageChanged(old_page, new_page)
{
    if(old_page == Manager.HOME_PAGE) {
        current_page=home_page_item
    } else if(old_page == Manager.THEMA_PAGE) {
        current_page=thema_page_item
    }else if(old_page == Manager.RESULT_PAGE) {
        current_page=result_page_item
    }else if(old_page == Manager.WORDS_PAGE) {
        current_page=words_page_item
    } else if(old_page== Manager.ABOUT_PAGE) {
        current_page=about_page_item
    }


    if(new_page == Manager.HOME_PAGE) {
        next_page=home_page_item
    } else if(new_page == Manager.THEMA_PAGE) {
        next_page=thema_page_item
    }else if(new_page == Manager.RESULT_PAGE) {
        next_page=result_page_item
    }else if(new_page == Manager.WORDS_PAGE) {
        next_page=words_page_item
    } else if(new_page== Manager.ABOUT_PAGE) {
        next_page=about_page_item
    }

    current_page.visible = false
    next_page.visible = true

    //state=state=="slide_in"?"":"slide_in"
}

}
