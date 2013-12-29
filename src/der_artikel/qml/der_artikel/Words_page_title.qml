import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {
    property int play_time: 1
    property alias timer_running:play_timer.running
    page_id: Manager.WORDS_PAGE
    Timer {
        id: play_timer
        interval: 1000
        repeat: true
        onTriggered: {
            if(play_time<=1) {
                running = false
                manager.current_page = Manager.RESULT_PAGE
            }

            if(play_time <=20) {
                timer_text.color = cp_blue.colorInfo
            }

            if(play_time <=10) {
                timer_text.color = cp_blue.colorWarn
            }

            timer_text.text = toTime(--play_time)
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
        text: qsTr("Infinite")
        font.family: custom_regular.name
        color:cp_blue.colorf01
        font.pixelSize: 20
    }

    onPlay_timeChanged: {
        timer_text.text = toTime(play_time)
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
