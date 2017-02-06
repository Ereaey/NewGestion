import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/"

Item {
    id:mainview
    ListModel {
           id: myModel
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }
           ListElement { data: "dqsd"; ide: 12058184 }

       }
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
            text:"Recherche d'un utilisateur"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

        }
        ButtonSt
        {
            x:parent.width - 210
            text: "Nouvelle recherche"
            y:10
            height: 30
            width: 200
            onClicked:
            {
                chooseCommu.open();
            }
        }
    }

    Rectangle
    {
        id:dataDomaine
        width: parent.width - 100
        height: t.height + 20

        color: "#181A29"
        y:80
        x:50
        radius: 5

        Column
        {
            id:t
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Utilisateur en cours de recherche"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"Nom Prenom : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Identifiant : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de documents : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de domaines responsable : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de domaines gestionnaire : "
                color:"white"
                font.pointSize: 10
            }


            Text
            {
                text:"Attention l'utilisateur n'appartient plus à la communauté"
                color:"red"
                font.pointSize: 10
            }

        }
    }

    Rectangle
    {
        width: parent.width - 100
        height: 90

        color: "#181A29"
        y: dataDomaine.y + dataDomaine.height + 10
        x:50
        radius: 5
        Text
        {
            text:"Visualiser dans l'arbre"
            color:"white"
            font.pointSize: 12
            x:20
            y:10
        }
        ComboBox {
            x:20
            y:40
            width: 300
            height: 25
            id:visuTree
            model: [ "Domaines responsable", "Domaines gestionnaire", "Documents propriétaire" ]
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
        ButtonSt
        {
            x: 330
            text: "Visualier"
            y:40
            height: 25
            width: 200
            onClicked:
            {
                chooseCommu.open();
            }
        }
    }

    Rectangle
    {
        width: parent.width - 100
        height: parent.height - dataDomaine.y - dataDomaine.height - 120

        color: "#181A29"
        y: dataDomaine.y + dataDomaine.height + 110
        x:50
        radius: 5
        Text
        {
            text:"Liste des documents: "
            color:"white"
            font.pointSize: 12
            x:20
            y:10
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
            model: myModel
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
                    text:"Nom du document : " + model.data + "  (" + model.ide + ")"
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Nom du responsable : " + model.ide
                    font.pointSize: 8
                    x:10
                    y:23
                }
            }

        }
    }


}
