import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id:page
    property int page_id
    x: manager.current_page === page_id ? 4 : width +16
    Behavior on x {
        SequentialAnimation {
            PauseAnimation { duration: (manager.current_page === page_id) ? 0 : 300}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===false ) {
                    if(manager.current_page !== page_id) {
                        page.visible=false
                    }
                } else {
                    if(manager.current_page === page_id) {
                        page.visible=true
                    }
                }
            }
        }
    }
    width:parent.width-8
    anchors.top: root_item.top
    anchors.bottom: root_item.bottom
    anchors.topMargin: 6
    anchors.bottomMargin: 6
}
