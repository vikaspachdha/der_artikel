import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {

    page_id: Manager.THEMA_PAGE

    Image {
        id:coin
        source: getTexture()
        visible: themaModel.selection_state === ThemaModel.SINGLE_SELECTION ? true:false
        anchors.left: parent.left
        anchors.top:parent.top
        anchors.bottom:parent.bottom
        anchors.leftMargin: 2
        width:height
        fillMode: Image.Stretch
        transform: Rotation {
            id: rotation
            origin.x: coin.width/2
            origin.y: coin.height/2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
            Behavior on angle {
                NumberAnimation{
                    duration: rotation.angle===0?800:0
                    onRunningChanged: {
                        if(running === false) {
                           rotation.angle = 0
                        }
                    }
                }
            }
        }

        Timer {
            interval: 4000
            running: true
            repeat: true
            onTriggered: {
                rotation.angle = 360
            }
        }
    }

    Text {
        id: heading_1
        text:{
            switch(themaModel.selection_state) {
            case ThemaModel.MULTIPLE_SELECTION:
                return qsTr("Multi Mode - Coming soon") + settings.i18n_empty_string
            default:
                return qsTr("Select Thema") + settings.i18n_empty_string
            }
        }

        anchors {
            top:parent.top
            left:parent.left
            leftMargin: 6
            topMargin: 6
        }
        visible: themaModel.selection_state === ThemaModel.SINGLE_SELECTION ? false:true
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_1_right
        text:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ?
                 qsTr("Experience : ") + settings.i18n_empty_string+themaModel.selected_thema.experience:""
        anchors {
            top:parent.top
            right:parent.right
            rightMargin:6
            topMargin: 6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_2_right
        text: {
            if(themaModel.selection_state===ThemaModel.SINGLE_SELECTION) {
                var currentState = themaModel.selected_thema.state
                var state_str = qsTr("State - ") + settings.i18n_empty_string
                switch(currentState) {
                case Thema.INERT:
                    state_str += qsTr("Inert") + settings.i18n_empty_string
                    break
                case Thema.GOLD:
                    state_str += qsTr("Gold") + settings.i18n_empty_string
                    break;
                case Thema.SILVER:
                    state_str += qsTr("Silver") + settings.i18n_empty_string
                    break;
                default:
                    state_str += qsTr("Rusty") + settings.i18n_empty_string
                    break;
                }
            } else {
                return ""
            }
            return state_str
        }

        anchors {
            bottom:parent.bottom
            bottomMargin: 6
            right:parent.right
            rightMargin:6
        }
        color: color_palette.color_font_01
        font.family: custom_regular.name
        font.pixelSize: 18
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    function getTexture()
    {
        var image_url = ""
        if(themaModel.selection_state===ThemaModel.SINGLE_SELECTION) {
            switch(themaModel.selected_thema.state) {
            case Thema.RUSTY:
                image_url = "qrc:/res/resources/50_cent_rusty.png";
                break;
            case Thema.SILVER:
                image_url = "qrc:/res/resources/50_cent_silver.png";
                break;
            case Thema.GOLD:
                image_url = "qrc:/res/resources/50_cent_gold.png";
                break;
            case Thema.INERT:
                image_url = "qrc:/res/resources/50_cent_inert.png";
                break;
            }
        }
        return image_url
    }
}
