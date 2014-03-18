import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    id:root
    page_id:Manager.STATS_PAGE

    property int thema_count:0
    property int inert_thema_count:0
    property int golden_thema_count:0
    property int silver_thema_count:0
    property int rusty_thema_count:0
    property string best_thema_name:""

    Flickable {
        anchors.fill: parent
        contentHeight: 6 * 32 + 12
        Repeater {
            model:6
            delegate: Noun_Item {
                x:6
                y: (index*32) + 6
                text: {
                    switch(index) {
                    case 0:return qsTr("Thema count : ") + thema_count + settings.i18n_empty_string
                    case 1:return qsTr("Best Thema : ")  + best_thema_name + settings.i18n_empty_string
                    case 2:return qsTr("Inert themas : ")  + inert_thema_count + settings.i18n_empty_string
                    case 3:return qsTr("Golden themas : ")  + golden_thema_count + settings.i18n_empty_string
                    case 4:return qsTr("Silver themas : ")  + silver_thema_count + settings.i18n_empty_string
                    case 5:return qsTr("Rusty themas : ")  + rusty_thema_count + settings.i18n_empty_string
                    }
                }
            }
        }
    }
}
