import QtQuick 2.1
import com.vystosi.qmlcomponents 1.0

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
        color:color_palette.color_btn_01
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
        anchors.rightMargin: 8
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

    Label {
        id:url_lbl
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:msgTimeSlider.bottom
        anchors.topMargin: 20
        lblText:qsTr("Thema update url")
    }

    Rectangle {
        id:url_input_rect
        anchors{top:url_lbl.bottom;left:parent.left;leftMargin: 8;right: parent.right;rightMargin: 8}
        height:url_input.contentHeight + 4
        radius: 4
        color:color_palette.color_btn_01
        clip:true
        TextInput {
            id:url_input
            width:parent.width-4
            anchors{centerIn: parent}
            selectByMouse: true
            onTextChanged: {
                settings.thema_remote_path = text;
            }
            Component.onCompleted: {
                url_input.text = settings.thema_remote_path
            }
        }
    }

    Button {
        id:update_thema_btn
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.top:url_input_rect.bottom
        anchors.topMargin: 20
        buttonText:qsTr("Update thema")
        onActivated: {
                themaUpdater.checkUpdate(url_input.text);

        }
    }

    Connections {
        target:themaUpdater
        onUpdateResponse: {

            switch(response_code) {

                case ThemaUpdater.UPDATE_STARTED:
                    messageBarInstance.showMsgAsync(qsTr("Updating thema"),"");
                    break;

                case ThemaUpdater.UPDATE_NOT_AVAILABLE:
                case ThemaUpdater.UPDATE_ERROR:
                case ThemaUpdater.UPDATE_ABORTED:
                case ThemaUpdater.UPDATE_FINISHED:
                    messageBarInstance.closeMsg()
                    break;
            }
        }

        onUpdateProgress: {
            msg_bar.message_txt = info;
            msg_bar.setProgress(progress)
        }
    }
}
