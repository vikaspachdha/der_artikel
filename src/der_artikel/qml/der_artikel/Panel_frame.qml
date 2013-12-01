import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: root_item

    property Item current_panel
    property Item next_panel


    Home_page_panel {
        id: home_page_panel_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible:true
    }

    Words_page_panel {
        id: words_page_panel_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible:false
    }

    Thema_page_panel {
        id: thema_page_panel_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible:false
    }

    Result_page_panel {
        id: result_page_panel_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible:false
    }

    About_page_panel {
        id: about_page_panel_item
        anchors.top: root_item.top
        anchors.right: root_item.right
        anchors.bottom: root_item.bottom
        anchors.left: root_item.left
        anchors.margins: 4
        visible:false
    }


Component.onCompleted: {
    current_panel = home_page_panel_item
    manager.currentPageChanged.connect(onCurrenPageChanged)
}


function onCurrenPageChanged(old_page, new_page)
{
    if(old_page == Manager.HOME_PAGE) {
        current_panel=home_page_panel_item
    } else if(old_page == Manager.THEMA_PAGE) {
        current_panel=thema_page_panel_item
    }else if(old_page == Manager.RESULT_PAGE) {
        current_panel=result_page_panel_item
    }else if(old_page == Manager.WORDS_PAGE) {
        current_panel=words_page_panel_item
    } else if(old_page == Manager.ABOUT_PAGE) {
        current_panel=about_page_panel_item
    }


    if(new_page == Manager.HOME_PAGE) {
        next_panel=home_page_panel_item
    } else if(new_page == Manager.THEMA_PAGE) {
        next_panel=thema_page_panel_item
    }else if(new_page == Manager.RESULT_PAGE) {
        next_panel=result_page_panel_item
    }else if(new_page == Manager.WORDS_PAGE) {
        next_panel=words_page_panel_item
    } else if(new_page == Manager.ABOUT_PAGE) {
        next_panel=about_page_panel_item
    }

    current_panel.visible = false
    next_panel.visible = true
    //state=state=="slide_in"?"":"slide_in"
}

}
