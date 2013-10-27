import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    //anchors.fill: parent
    ListModel
    {
        id: page_model
        ListElement { title:"Thema"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.THEMA_PAGE}
        ListElement { title:"Result"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.RESULT_PAGE}
        ListElement { title:"words page"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.WORDS_PAGE}
        ListElement { title:"About"; icon_src:"qrc:/res/resources/default_thema.png";src_page_id:Manager.ABOUT_PAGE}
    }

    GridView {
        id: grid1
        anchors.fill: parent
        model:page_model
        delegate: Page_item {
            label_text: title
            page_icon: icon_src
            page_id:src_page_id
        }
    }
}
