import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Title_bar {

    y: manager.current_page === Manager.THEMA_PAGE ? 0 : -height
    Behavior on y {
        NumberAnimation { duration:400 }
    }

    Image {
        id: page_icon
        width: height
        anchors {
            top:parent.top
            left:parent.left
            bottom: parent.bottom
            margins:12
        }
        source:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ? themaModel.selected_thema.icon_url:""
        fillMode: Image.PreserveAspectFit
        horizontalAlignment: Image.AlignLeft
        verticalAlignment: Image.AlignTop
    }


    Text {
        id: heading_1
        text:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ? themaModel.selected_thema.name:qsTr("Select Thema")
        anchors {
            top:parent.top
            left:page_icon.right
            leftMargin: 12
            topMargin: 8
        }
        font.pixelSize: 16
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignVCenter
    }

    Text {
        id: heading_1_right
        text:themaModel.selection_state===ThemaModel.SINGLE_SELECTION ? themaModel.selected_thema.word_count + qsTr(" Words"):""
        anchors {
            top:parent.top
            right:parent.right
            rightMargin:10
            topMargin: 8
        }
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
            left:page_icon.right
            leftMargin: 12
        }
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
                    if(currentState===Thema.RUSTY) {
                        return qsTr("Rusty")
                    }
                    if (currentState===Thema.SILVER) {
                        return qsTr("Silver")
                    }
                    if (currentState===Thema.GOLD) {
                        return qsTr("Gold")
                    }
                    return qsTr("Inert")
                } else {
                    return ""
                }
            }

        anchors {
            top:heading_1.bottom
            right:parent.right
            rightMargin:10
        }
        font.pixelSize: 18
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignLeft
        verticalAlignment:  Text.AlignTop
    }
}
