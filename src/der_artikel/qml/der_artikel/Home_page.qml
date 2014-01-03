import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.HOME_PAGE
    ListModel
    {
        id: page_model
        ListElement { title:"Thema"; icon_src:"qrc:/res/resources/thema.png";src_page_id:Manager.THEMA_PAGE}
        ListElement { title:"Result"; icon_src:"qrc:/res/resources/result.png";src_page_id:Manager.RESULT_PAGE}
        ListElement { title:"Statistics"; icon_src:"qrc:/res/resources/stats.png";src_page_id:Manager.STATS_PAGE}
        ListElement { title:"Help"; icon_src:"qrc:/res/resources/help.png";src_page_id:Manager.HELP_PAGE}
        ListElement { title:"Settings"; icon_src:"qrc:/res/resources/settings.png";src_page_id:Manager.SETTINGS_PAGE}
        ListElement { title:"About"; icon_src:"qrc:/res/resources/about.png";src_page_id:Manager.ABOUT_PAGE}
    }

    GridView {
        id: grid1
        anchors.fill: parent
        model:page_model
        cellWidth:84
        cellHeight:94
        delegate: Page_item {
            label_text: title
            page_icon: icon_src
        }
    }
}
