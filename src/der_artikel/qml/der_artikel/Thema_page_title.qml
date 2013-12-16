import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {

    page_id: Manager.THEMA_PAGE

    Text {
        id: heading_1
        text:{
                switch(themaModel.selection_state) {
                    case ThemaModel.MULTIPLE_SELECTION:
                        return qsTr("Multi Mode - Coming soon")
                    case ThemaModel.SINGLE_SELECTION:
                        return themaModel.selected_thema.name
                    default:
                        return qsTr("Select Thema")
                }
            }

        anchors {
            top:parent.top
            left:parent.left
            leftMargin: 12
            topMargin: 10
        }
        color: cp_blue.colorf01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_1_right
        text:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ? qsTr("Experience : ")+themaModel.selected_thema.experience:""
        anchors {
            top:parent.top
            right:parent.right
            rightMargin:10
            topMargin: 10
        }
        color: cp_blue.colorf01
        font.family: custom_regular.name
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_2
        text:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ? themaModel.selected_thema.name:""
        anchors {
            top:heading_1.bottom
            left:parent.left
            leftMargin: 12
        }
        color: cp_blue.colorf01
        font.family: custom_regular.name
        font.pixelSize: 12
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }

    Text {
        id: heading_2_right
        text: {
                if(themaModel.selection_state===ThemaModel.SINGLE_SELECTION) {
                    var currentState = themaModel.selected_thema.state
                    var state_str = qsTr("State - ")
                    switch(currentState) {
                        case Thema.INERT:
                            state_str += qsTr("Inert")
                            break
                        case Thema.GOLD:
                            state_str += qsTr("Gold")
                            break;
                        case Thema.SILVER:
                            state_str += qsTr("Silver")
                            break;
                        default:
                            state_str += qsTr("Rusty")
                            break;
                    }
                } else {
                    return ""
                }
                return state_str
            }

        anchors {
            bottom:parent.bottom
            bottomMargin: 10
            right:parent.right
            rightMargin:10
        }
        color: cp_blue.colorf01
        font.family: custom_regular.name
        font.pixelSize: 18
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }
}
