import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

Item{


RowLayout
{
    anchors.fill: parent
    spacing: 0


    Rectangle
    {
        Layout.fillHeight: true
        Layout.alignment: Qt.AlignRight
        color: "#364150"
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
        initialItem: "qrc:MainMenu.qml"
    }

    }




}
