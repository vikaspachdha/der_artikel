import QtQuick 2.0
import QtQuick.Controls 1.0

Page_panel {
    ExclusiveGroup {
        id: articleGroup
    }

    Column {
        id: articleCol
        anchors.verticalCenter: parent.verticalCenter
        spacing: 16
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

}
