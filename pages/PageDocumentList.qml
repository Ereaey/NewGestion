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
            text:"Goals vides"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

        }
    }

    Rectangle
    {
        width: parent.width - 100
        height: parent.height - 105

        color: "#181A29"
        y:85
        x:50
        radius: 5

        Text
        {
            text:"Liste des documents"
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
            model: treatment.listDoc
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
                    text:"Nom du document : " + model.modelData.nom + "("+ model.modelData.id +")"
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Nom du propriétaire : " + model.modelData.proprio
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x:parent.width - 110
                    text: "Voir le domaine"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchDomaine(model.modelData.iddomaine);
                        swipeView.replace("qrc:pages/PageDomaineSearch.qml", StackView.Immediate);
                    }
                }
                ButtonSt
                {
                    x:parent.width - 220
                    text: "Voir propriétaire"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchUserId(model.modelData.idproprio, 0);
                        swipeView.replace("qrc:pages/PageUtilisateurSearch.qml", StackView.Immediate);
                    }
                }
            }

        }

        }



}
