import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/"

Item {
    id:goalMenu

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
        source:"qrc:../images/logo2.jpg"
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
            source:"qrc:../images/icon.png"
            Text
            {
                y:80
                text:"Accueil"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:MainMenu.qml");
                }
            }
        }
        Image
        {
            source:"qrc:../images/magnifying-glass.png"
            Text
            {
                y:80
                text:"Rechercher Domaine"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:pages/PageDomaineSearch.qml");
                }
            }
        }
        Image
        {
            source:"qrc:../images/file.png"
            Text
            {
                y:80
                text:"Domaines Vides"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:pages/PageGoalList.qml");
                }
            }
        }
        Image
        {
            source:"qrc:../images/folder.png"
            Text
            {
                y:80
                text:"Domaines"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            Text
            {
                y:110
                text:"surchargés"
                color: "white"
                font.pointSize:16
                x:parent.width/2 - width/2
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:pages/PageGoalList.qml");
                }
            }
        }


    }


}
