import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: root_item
    width:108

    Home_page_panel {
        id: home_page_panel_item
        width:100
        height:parent.height
    }

    Words_page_panel {
        id: words_page_panel_item
        width:100
        height:parent.height
    }

    Thema_page_panel {
        id: thema_page_panel_item
        width:100
        height:parent.height
    }

    Result_page_panel {
        id: result_page_panel_item
        width:100
        height:parent.height
    }

    Help_page_panel {
        id: help_page_panel_item
        width:100
        height:parent.height
    }

    Stats_page_panel {
        id: stats_page_panel_item
        width:100
        height:parent.height
    }

    About_page_panel {
        id: about_page_panel_item
        width:100
        height:parent.height
    }

}
