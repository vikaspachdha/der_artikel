import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

Item {
    id:page
    property int page_id
    x : width +16
    Behavior on x {
        SequentialAnimation {
            PauseAnimation { id: animPause;}
            NumberAnimation { duration:200; easing.type: Easing.InOutElastic; easing.amplitude: 2.0; easing.period: 2.0}
            onRunningChanged: {
                if(running===true ) {
                    // Animation starting
                    if(manager.current_page == page_id) {
                        animPause.duration=0
                    } else {
                        animPause.duration=300
                    }
                } else {
                    // Animation stopped
                    if(manager.current_page !== page_id) {
                        page.destroy()
                    }
                }
            }
        }
    }

    Connections {
        target:manager
        onCurrentPageChanged: {
            x = manager.current_page === page_id ? 4 : width +16
        }
    }
    width:parent.width-8
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.topMargin: 6
    anchors.bottomMargin: 6
    clip:true

    Component.onCompleted: {
        manager.setPageItem(page_id,page)
        x = 4
    }
}
