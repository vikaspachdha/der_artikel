import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import com.vystosi.qmlcomponents 1.0

Page_panel {
    ExclusiveGroup {
        id: articleGroup
    }

    Column {
        id: articleCol
        anchors.top: parent.top
        anchors.left: parent.left
        spacing: 4
        RadioButton {
            id: mannlisch
            text: "Der"
            exclusiveGroup: articleGroup
            checked: true
            onCheckedChanged: {
                if(checked) {
                    manager.selected_article = 1
                }
                currentColor = "red"
            }
        }
        RadioButton {
            text: "Die"
            exclusiveGroup: articleGroup
            onCheckedChanged: {
                if(checked) {
                    manager.selected_article = 2
                }
                currentColor = "pink"
            }
        }
        RadioButton {
            text: "Das"
            exclusiveGroup: articleGroup
            onCheckedChanged: {
                if(checked) {
                    manager.selected_article = 3
                }
                currentColor = "lightgray"
            }
        }
        RadioButton {
            text: "None"
            exclusiveGroup: articleGroup
            onCheckedChanged: {
                if(checked) {
                    manager.selected_article = 4
                }
                currentColor = "lightgray"
            }
        }
    }
    Command_item
    {
        id: home_cmd
        //anchors.left: parent.left
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        cmd_text: qsTr("Finish")
        cmd_icon: "qrc:/res/resources/result_32.png"
        onCommandActivated: {
            manager.calculateResult()
            manager.current_page = Manager.RESULT_PAGE
        }
    }

}
