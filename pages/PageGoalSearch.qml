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
            text:"Recherche d'un goal"
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
        width: parent.width - 100
        height: 80

        color: "#181A29"
        y:80
        x:50
        radius: 5

        Text
        {
            text:"Goal en cours de recherche : G_H_DEUR"
            x:20
            y:10
            color:"white"
            font.pointSize: 12
            ButtonSt
            {
                x:parent.width + 20
                text: "Voir la fiche"
                height:20
                onClicked:
                {
                    chooseCommu.open();
                }
            }

        }

        Text
        {
            text:"Nombres de domaines : 1204"
            x:20
            y:33
            color:"white"
            font.pointSize: 10
        }
        Text
        {
            text:"Modes de recherche : Gestionnaire"
            x:20
            y:50
            color:"white"
            font.pointSize: 10
        }
    }

    Rectangle
    {
        width: parent.width - 100
        height: parent.height - 200

        color: "#181A29"
        y:180
        x:50
        radius: 5

        Text
        {
            text:"Liste des domaines séléctionés"
            x:20
            y:10
            color:"white"
            font.pointSize: 12
        }
        ButtonSt
        {
            x:parent.width - 130
            text: "Vider"
            height:20
            y:10
            onClicked:
            {
                chooseCommu.open();
            }
        }
        ButtonSt
        {
            x:parent.width - 240
            text: "Exporter"
            height:20
            y:10
            onClicked:
            {
                chooseCommu.open();
            }
        }

        Flickable
        {
            width:parent.width - 5
            height:parent.height - 70
            y:50
            x:5

            flickableDirection: Flickable.VerticalFlick

            ListView
            {
                clip: true
                spacing: 10
                maximumFlickVelocity: 100
                height: parent.height
                width: parent.width
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
                        text:"Nom du domaine : " + model.data
                        font.pointSize: 10
                        x:10
                        y:5
                        id:ndDomaine
                    }
                    Text
                    {
                        color: "white"
                        text:"Id du domaine : " + model.ide
                        font.pointSize: 8
                        x:10
                        y:23
                    }
                    ButtonSt
                    {
                        x:parent.width - 220
                        text: "Voir la fiche"
                        height:30
                        y:5
                        onClicked:
                        {
                            chooseCommu.open();
                        }
                    }
                    ButtonSt
                    {
                        x: parent.width - 110
                        text: "Copier"
                        height:30
                        y:5
                        onClicked:
                        {
                            chooseCommu.open();
                        }
                    }
                }

            }
            //ScrollBar.vertical: ScrollBar {}
            //clip: true
        }

        }



}
