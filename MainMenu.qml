import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4


Item {
    id:mainview

    Rectangle
    {
        width: 600
        height: parent.height
        x:parent.width/2 - width/2
        y:0


        color: "#181A29"
    }
    Image
    {
        id:logo
        x:parent.width/2 - width/2
        y:-50
        width: 600
        source:"qrc:images/logo2.jpg"
    }
    GridLayout
    {
        id: grid
        columns: 3
        rowSpacing: 150
        columnSpacing: 150
        x:parent.width/2 - width/2
        y:parent.height/2 - height/2 + 100
        Image
        {
            source:"qrc:images/question-list.png"
            Text
            {
                y:80
                text:"Notation"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:pages/PageNotation.qml", StackView.Immediate);
                }
            }
        }
        Image
        {
            source:"qrc:images/file.png"
            Text
            {
                y:80
                text:"Documents"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:menu/DocumentMenu.qml", StackView.Immediate);
                }
            }
        }
        Image
        {
            source:"qrc:images/folder.png"
            Text
            {
                y:80
                text:"Domaines"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:menu/DomaineMenu.qml", StackView.Immediate);
                }
            }
        }
        Image
        {
            source:"qrc:images/group.png"
            Text
            {
                y:80
                text:"Goals"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:menu/GoalMenu.qml", StackView.Immediate);
                }
            }
        }
        Image
        {
            source:"qrc:images/settings.png"

            Text
            {
                y:80
                text:"Procédures"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
        }
        Image
        {
            source:"qrc:images/user.png"
            Text
            {
                y:80
                text:"Utilisateurs"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:menu/UserMenu.qml", StackView.Immediate);
                }
            }
        }

    }


}
