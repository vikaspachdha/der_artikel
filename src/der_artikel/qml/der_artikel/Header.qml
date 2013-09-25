import QtQuick 2.0

Rectangle {
    id: headerItem
    gradient: Gradient {
              GradientStop { position: 0.0; color: "#8E9CA4" }
              GradientStop { position: 0.10; color: "#9CAFB8" }
              GradientStop { position: 0.90; color: "#9CAFB8" }
              GradientStop { position: 1.0; color: "#8E9CA4" }
          }

    Text {
        id: themaLabel
        text:"Thema : Wohnung"
        anchors {
            top:parent.top
            right:parent.right
            rightMargin: 4
        }
    }
    Text {
        id: themaTrLabel
        text:"Residential"
        anchors {
            top:themaLabel.bottom
            right:parent.right
            rightMargin: 4
        }
    }
}
