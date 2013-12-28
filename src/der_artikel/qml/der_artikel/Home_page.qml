import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.HOME_PAGE
    ListModel
    {
        id: page_model
        ListElement { title:"Thema"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.THEMA_PAGE}
        ListElement { title:"Result"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.RESULT_PAGE}
        ListElement { title:"Statistics"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.STATS_PAGE}
        ListElement { title:"Help"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.HELP_PAGE}
        ListElement { title:"Settings"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.PREF_PAGE}
        ListElement { title:"About"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.ABOUT_PAGE}
    }

    GridView {
        id: grid1
        anchors.fill: parent
        model:page_model
        cellWidth:65
        cellHeight:75
        delegate: Page_item {
            label_text: title
            page_icon: icon_src
        }
    }
}
