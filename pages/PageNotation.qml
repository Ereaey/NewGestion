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
    Flickable
    {
        anchors.fill: parent
        contentHeight: teee.height + 120
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
            text:"Note de la communauté"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

        }
    }

    Column
    {
        id:teee
        y:80
        width: parent.width
        spacing: 20
        Rectangle
        {
            width: parent.width - 100
            height: 30
            color: "#181A29"
            y:0
            x:50
            radius: 5
            Text
            {
                x:20
                y:5
                text:"Note de la communauté : 25 / 100"
                color:"white"
                font.pointSize: 12
                font.bold: true
            }
        }

    Rectangle
    {
        width: parent.width - 100
        height: t.height + 20

        color: "#181A29"
        y:0
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
                text:"Etat communauté"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"Nb de membres de la communauté via GOALs (doublons exclus) : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nb de documents : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nb de domaines (avec la racine) : 1204"
                color:"white"
                font.pointSize: 10
            }

            Text
            {
                text:"Nb de niveaux de domaines dans la communauté : "
                color:"white"
                font.pointSize: 10
            }

        }
    }
    Rectangle
    {
        width: parent.width - 100
        height: t2.height + 20

        color: "#181A29"
        x:50
        radius: 5

        Column
        {
            id:t2
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Responsables - Propriétaires"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"% Documents dont le Propriétaire n'appartient pas à la communauté : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% Documents dont le Propriétaire n'est plus dans l'annuaire PSA : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% Domaines dont le Responsable n'appartient pas à la communauté : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% Gestionnaires  n'appartenant pas à la communauté : 1204"
                color:"white"
                font.pointSize: 10
            }

            Text
            {
                text:"% Domaines dont au moins un gestionnaire n'appartient pas à la communauté (doublons inclus) : "
                color:"white"
                font.pointSize: 10
            }

        }
    }
    Rectangle
    {
        width: parent.width - 100
        height: t3.height + 20

        color: "#181A29"
        x:50
        radius: 5

        Column
        {
            id:t3
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Etat des documents"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"% documents publiés : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% docs en version de travail depuis plus de 6 mois : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% Domaines dont le Responsable n'appartient pas à la communauté : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% docs avec trop de PJ : 1204"
                color:"white"
                font.pointSize: 10
            }
        }
    }
    Rectangle
    {
        width: parent.width - 100
        height: t4.height + 20

        color: "#181A29"
        x:50
        radius: 5

        Column
        {
            id:t4
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Goals"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"nb de Goals inexistants utilisés : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"nb de Goals avec 0 membre utilisés : "
                color:"white"
                font.pointSize: 10
            }
        }
    }
    Rectangle
    {
        width: parent.width - 100
        height: t5.height + 20

        color: "#181A29"
        x:50
        radius: 5

        Column
        {
            id:t5
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Répartition des documents dans les domaines"
                color:"white"
                font.pointSize: 12
            }
            Text
            {
                text:"% domaines vides (sans document ni sous-domaine) : "
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"% domaines avec un nombre de documents trop important : "
                color:"white"
                font.pointSize: 10
            }
        }
    }
    }
    }


}
