import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/"

Item {
    id:mainview
    Rectangle
    {
        width: parent.width - 100
        height: 50

        color: "#181A29"
        y:25
        x:50
        radius: 3
        Image
        {
            x:10
            width:40
            height: 40
            y:5
            source:"qrc:../images/icon.png"
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    swipeView.replace("qrc:MainMenu.qml", StackView.Immediate);
                }
            }
        }
        Text
        {
            text:"Utilisateurs"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

        }
    }
/*
    Rectangle
    {
        width: parent.width - 100
        height: 50
        color: "#181A29"
        y:85
        x:50
        radius: 5
        ComboBox {
            x:20
            y:12
            width: parent.width - 40
            height: 25
            id:visuTree
            model: [ "Responsables", "Gestionnaires", "Propriétaires" ]
            background: Rectangle {
                implicitWidth: 100
                implicitHeight: 20

                opacity: enabled ? 1 : 0.3
                //color: visuTree.pressed ? (visuTree.highlighted ? "#585a5c" : "#e4e4e4") : (visuTree.highlighted ? "#353637" : "#f6f6f6")
                border.color: visuTree.pressed ? "#26282a" : "#353637"
                border.width: 1

                radius:3
            }


        }
    }*/

    Rectangle
    {
        width: parent.width - 100
        height: parent.height - 165

        color: "#181A29"
        y:145
        x:50
        radius: 5

        Text
        {
            text:"Liste des utilisateurs"
            x:20
            y:10
            color:"white"
            font.pointSize: 12
        }
        ListView
        {
            ScrollBar.vertical: ScrollBar{active: true}
            y:50
            x:5
            clip: true
            spacing: 10
            maximumFlickVelocity: 600
            highlightMoveVelocity : 600
            width:parent.width - 15
            height:parent.height - 70
            id:autoCompletList
            model: treatment.listUser
            delegate: Rectangle
            {
                width: parent.width - 40
                x:20
                height: 40
                radius: 3
                color: "#364150"
                y:40
                Text
                {
                    color: "white"
                    text:"Nom de l'utilisateur : " + model.modelData.nom
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Identifiant : " + model.modelData.id
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x:parent.width - 110
                    text: "Rechercher"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchUserId(model.modelData.id, 0);
                        swipeView.replace("qrc:pages/PageUtilisateurSearch.qml", StackView.Immediate);
                    }
                }
            }

        }

        }



}
