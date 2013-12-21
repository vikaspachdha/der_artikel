import QtQuick 2.0
import com.vystosi.qmlcomponents 1.0

Page {
    page_id:Manager.RESULT_PAGE
    id: rectangle1

    Custom_label {
        id: title_label
        text: list_view.count>0 ? qsTr("Mistakes") : qsTr("No Mistakes")
        font_color:cp_blue.colorf02
        gradient: Gradient {
            GradientStop {position:0.0;color:cp_blue.colorBg02}
            GradientStop {position:0.1;color:cp_blue.colorBg01}
            GradientStop {position:0.9;color:cp_blue.colorBg01}
            GradientStop {position:1.0;color:cp_blue.colorBg02}
        }
        radius:4
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    ListView {
        id: list_view

        anchors.top: title_label.bottom
        anchors.topMargin: 2
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        spacing:2
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

}
