import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/mycomponent"

Item {
    id:mainview
    function showDomaine(idd)
    {
        var iddomaineespace = idd.substring(0, 3) + " " + idd.substring(3, 6) + " " + idd.substring(6, 9);
        return iddomaineespace;
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
            text:treatment.currentAction
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
            text:"Liste des domaines"
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
            model: treatment.listDom
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
                    text:"Nom du domaine : " + model.modelData.nom + "     (" + showDomaine(model.modelData.iddomaine) +")"
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Responsable : " + model.modelData.responsable + "  " + model.modelData.idresponsable
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x:parent.width - 220
                    text: "Voir responsable"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchUserId(model.modelData.idresponsable, 0);
                        swipeView.replace("qrc:pages/PageUtilisateurSearch.qml", StackView.Immediate);
                    }
                }
                ButtonSt
                {
                    x:parent.width - 110
                    text: "Localiser"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchDomaine(model.modelData.iddomaine);
                        swipeView.replace("qrc:pages/PageDomaineSearch.qml", StackView.Immediate);
                    }
                }

            }

        }

        }



}
