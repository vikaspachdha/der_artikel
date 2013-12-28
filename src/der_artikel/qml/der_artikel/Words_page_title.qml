import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {
    property int time_in_secs: 3610
    page_id: Manager.WORDS_PAGE
    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: {
            timer_text.text = toTime(--time_in_secs)
        }
    }

    Text {
        id: timer_title
        anchors {
            right: parent.right
            rightMargin: 6
            top:parent.top
            topMargin: 6
        }
        text: qsTr("Remaining time")
        font.family: custom_regular.name
        color:cp_blue.colorf01
        font.pixelSize: 20
    }

    Text {
        id: timer_text
        anchors {
            right: parent.right
            rightMargin: 6
            bottom:parent.bottom
            bottomMargin: 6
        }
        text: qsTr("00:00:00")
        font.family: custom_regular.name
        color:cp_blue.colorf01
        font.pixelSize: 20
    }

    function toTime(secs) {
        var hours = (secs/3600)|0
        secs -= (hours*3600);
        var mins = (secs/60)|0;
        secs -= (mins*60);

        return pad(hours,2)+":"+pad(mins,2)+":"+pad(secs,2)
    }

    function pad (number, max) {
        var str = number.toString()
        return str.length < max ? pad("0" + str, max-1) : str;
    }
}
