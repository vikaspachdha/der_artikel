import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtGraphicalEffects 1.0
import com.vystosi.qmlcomponents 1.0
Image {
    id: rootItem;
    width: 400
    height: 400
    clip:true
    source: "qrc:/res/resources/background_texture.png"
    fillMode: Image.Tile
    horizontalAlignment: Image.AlignLeft
    verticalAlignment: Image.AlignTop
    property color currentColor

    Title_bar {
        id: title_item
        height: rootItem.height*0.2
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Panel_frame {
        id: cmd_panel_frame
        anchors.top: title_item.bottom
        anchors.bottom: home_cmd.top
        anchors.left: rootItem.left
        width: 80
    }

    Command_item
    {
        id: home_cmd
        //anchors.left: parent.left
        anchors.horizontalCenter: cmd_panel_frame.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        cmd_text: qsTr("Home")
        cmd_icon: "qrc:/res/resources/home.png"
        onCommandActivated: {
            manager.current_page = Manager.HOME_PAGE
        }
    }


    Content_frame
    {
        id: content_frame
        anchors.top: title_item.bottom
        anchors.bottom: rootItem.bottom
        anchors.left: cmd_panel_frame.right
        anchors.right: rootItem.right
    }


    function addWord(itemText)
    {
        var WordItem = content_frame.word_page.appendWordToFlow(itemText)
        return WordItem;
    }

    function showMessage()
    {
        msg_bar.animate = true
    }

    Message_bar {
        id: msg_bar
        height: parent.height * 0.2
        color:"red"

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottomMargin:8
    }

    DropShadow {
        anchors.fill: msg_bar
        horizontalOffset: 4
        verticalOffset: 8
        radius: 0
        spread: 0.3
        samples: 16
        color: "#66000000"
        source: msg_bar
    }

    function onCurrenPageChanged(old_page_id, new_page_id)
    {
        home_cmd.visible = new_page_id == Manager.HOME_PAGE ? false : true
    }

    Component.onCompleted: {
        manager.currentPageChanged.connect(onCurrenPageChanged)
    }
}

