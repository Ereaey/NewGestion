import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

ApplicationWindow {
    visible: true
    width: 1440
    height: 900
    title: qsTr("Hello World")

    background:Rectangle
    {
        color: "#25273C"
    }

    header:    Rectangle
    {
        width: parent.width
        height: 30
        x:0
        y:0
        color: "#181A29"
        Text
        {
            y:5
            x:parent.width - width - 120
            text:"Support assurane qualité opérationnel sites industriels valenciennes sevelnord et douvrin - FM"
            color: "white"
            font.family: "Arial"
            font.pointSize: 10
            //width: parent.width - 20
            //x:parent.width/2-width/2
            ButtonSt
            {
                x:parent.width+10
                text: "Modifier"
                height:15
                onClicked:
                {
                    chooseCommu.open();
                }
            }
        }
    }

    Popup {
        id: chooseCommu
        x: parent.width/2 - width/2
        y: 100
        width: 600
        height: parent.height - 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background:Rectangle
        {
            color: "#181A29"
            border.width : 2
            border.color: "white"
        }
    }

RowLayout
{
    anchors.fill: parent
    spacing: 0


    Rectangle
    {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignRight
        color: "#181A29"
        id:tree
        width: 500
        visible: false
        height: parent.height
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {

            }
        }
        border.width: 1
        border.color: "black"
    }

    Rectangle
    {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignRight
        width: 40
        height: parent.height
        color: "#181A29"
        Image
        {
            y:parent.height/2 - height/2
            x:3
            source:"qrc:images/play-button.png"
            mirror: tree.visible
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                tree.visible = !tree.visible;
            }
        }
        border.width: 1
        border.color: "black"
    }

    StackView {
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignLeft
        id: swipeView
        initialItem: "qrc:pages/PageGoalSearch.qml"
    }

    }




}
