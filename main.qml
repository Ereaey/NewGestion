import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
//import Qt.labs.controls 1.0
import QtQuick.Layouts 1.3
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
        ScrollView
        {
            y:30
            width: parent.width
            height: parent.height - 30
            ListView
            {
                anchors.fill: parent
                maximumFlickVelocity: 100
                id:testTree
                model: treet.tree
                focus: true
                delegate: ItemView{}
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
