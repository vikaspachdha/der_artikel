import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Item {
    id: rectangle1

    width: 800
    height: 600



    Custom_label {
        id: title_label
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Custom_label {
        id: score_label
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: title_label.bottom
        anchors.topMargin: 2
        font_size:14
    }

    Custom_label {
        id: mistakes_label
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: score_label.bottom
        anchors.topMargin: 2
        font_size:12
    }

    Custom_label {
        id: unplayed_label
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: mistakes_label.bottom
        anchors.topMargin: 2
        font_size:12
    }


    ListView {
        id: list_view1

        anchors.top: unplayed_label.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing:4
        clip:true
        model: currentResult.incorrectWordsModel
        delegate: Result_item {
            height: 20
            item_title: articleText(article)+" " + word_text
            item_result: articleText(user_article) + " " + word_text
        }
    }

    function onResultUpdated()
    {
        title_label.text = currentResult.grade_string
        score_label.text = currentResult.score_string
        mistakes_label.text = currentResult.mistake_string
        unplayed_label.text = currentResult.unplayed_string
    }

    Component.onCompleted: {
        currentResult.resultUpdated.connect(onResultUpdated)
    }

}
