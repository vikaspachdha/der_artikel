import QtQuick 2.0

Item {
    anchors.fill: parent
    Label {
        id:msg_time_lbl
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:parent.top
        anchors.topMargin: 8
        lblText:qsTr("Word info Time (in msecs)")
    }
    Rectangle {
        id:msg_time_input_rect
        anchors{top:msg_time_lbl.bottom;left:parent.left;leftMargin: 8}
        width:40
        height:msg_time_input.contentHeight + 4
        radius: 4
        TextInput {
            id:msg_time_input
            width:parent.width
            anchors{centerIn: parent}
            text:settings.word_msg_time_str
            validator: IntValidator{bottom:settings.min_word_msg_time;top:settings.max_word_msg_time}
            onTextChanged: {
                settings.word_msg_time_str = text;
            }
        }
    }

    Slider {
        id:msgTimeSlider
        property bool update_value: true
        property int  msec_range: settings.max_word_msg_time - settings.min_word_msg_time
        anchors.verticalCenter: msg_time_input_rect.verticalCenter
        anchors.left: msg_time_input_rect.right
        anchors.leftMargin: 4
        anchors.right: parent.right
        onValueChanged: {
            update_value = false
            settings.word_msg_time = (value * msec_range) + settings.min_word_msg_time
            update_value = true;
        }

        Connections {
            target:settings
            onWordMsgTimeChanged : {
                if(msgTimeSlider.update_value) {
                    msgTimeSlider.setValue((settings.word_msg_time - settings.min_word_msg_time)/msgTimeSlider.msec_range)
                }
            }
        }
        Component.onCompleted: {
            msgTimeSlider.setValue((settings.word_msg_time - settings.min_word_msg_time)/msec_range)
        }
    }
}
