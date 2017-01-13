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
                    swipeView.replace("qrc:MainMenu.qml");
                }
            }
        }
        Text
        {
            text:"Recherche d'un domaine"
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

        ButtonSt
        {
            x:parent.width - 110
            text: "Exporter plan"
            height:25
            y:10
            onClicked:
            {
                chooseCommu.open();
            }
        }
        Column
        {
            id:t
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Domaine en cours de recherche"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"Nom du domaine : "
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
                text:"Propriétaire : 1204"
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Gestionnaires : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Modificateurs : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Lecteurs : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Goals Gestionnaires: "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Goals Modificateurs: "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Goals Lecteurs : "
                color:"white"
                font.pointSize: 10
            }

            Text
            {
                text:"Nombre total de sous-domaines dans l'arborescence : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Niveau de confidentialité : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Domaine asservisseur: "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Documents synchronisés: "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Documents masqués: "
                color:"white"
                font.pointSize: 10
            }

        }
    }

    Rectangle
    {
        width: parent.width - 100
        height: parent.height - dataDomaine.y - dataDomaine.height - 20

        color: "#181A29"
        y: dataDomaine.y + dataDomaine.height + 10
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
                    text:"Nom du document : " + model.data + "(" + model.ide + ")"
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
                ButtonSt
                {
                    x:parent.width - 110
                    text: "Copier ID"
                    height:30
                    y:5
                    onClicked:
                    {
                        chooseCommu.open();
                    }
                }
                ButtonSt
                {
                    x:parent.width - 250
                    text: "Rechercher responsable"
                    height:30
                    y:5
                    onClicked:
                    {
                        chooseCommu.open();
                    }
                }
            }

        }
    }


}
