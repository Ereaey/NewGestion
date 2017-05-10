import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/mycomponent"

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
            id:comboRole
            model: [ "Responsables", "Gestionnaires", "Propriétaires", "Tous"]
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
    }



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
            spacing: 0
            maximumFlickVelocity: 600
            highlightMoveVelocity : 600
            width:parent.width - 15
            height:parent.height - 70
            id:listUserD
            model: treatment.listUser
            delegate: Rectangle
            {
                property bool vis:  model.modelData.nbDomaineRespon > 0 && comboRole.currentIndex === 0 ? true : model.modelData.nbDomaineGest > 0 && comboRole.currentIndex === 1 ? true : model.modelData.nbDocument > 0 && comboRole.currentIndex === 2 ? true : comboRole.currentIndex === 3 ? true : false
                width: vis ? parent.width - 40 : 0
                x:vis ? 20 : 0
                height: vis ? 95 : 0
                radius: vis ? 3 : 0
                visible: vis
                y: vis ? 40 : 0
                color: "transparent"
                Rectangle
                {
                radius: 3
                color: "#364150"
                width :parent.width
                height:parent.height - 10
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
                    y:17
                }
                Text
                {
                    color: "white"
                    text:"Documents propriétaire : " + model.modelData.nbDocument
                    font.pointSize: 8
                    x:10
                    y:30
                    //visible: model.modelData.nbDocument > 0 ? true : false
                }
                Text
                {
                    color: "white"
                    //visible: model.modelData.nbDomaineRespon > 0 ?  true : false
                    text:"Domaine responsable : " + model.modelData.nbDomaineRespon
                    font.pointSize: 8
                    x:10
                    y:40
                }
                Text
                {
                    color: "white"
                    //visible: model.modelData.nbDomaineGest > 0 ?  true : false
                    text:"Domaine gestionnaire : " + model.modelData.nbDomaineGest
                    font.pointSize: 8
                    x:10
                    y:50
                }
                Text
                {
                    color: "white"
                    //visible: model.modelData.nbDomaineLect > 0 ?  true : false
                    text:"Domaine lecteur : " + model.modelData.nbDomaineLect
                    font.pointSize: 8
                    x:10
                    y:60
                }
                Text
                {
                    color: "white"
                    //visible: model.modelData.nbDomaineModif > 0 ?  true : false
                    text:"Domaine modificateur : " + model.modelData.nbDomaineModif
                    font.pointSize: 8
                    x:10
                    y:70
                }

                ButtonSt
                {
                    visible: vis
                    x:parent.width - 110
                    text: "Rechercher"
                    height:50
                    y:12
                    onClicked:
                    {
                        treatment.searchUserId(model.modelData.id, 0);
                        swipeView.push("qrc:pages/PageUtilisateurSearch.qml", StackView.Immediate);
                    }
                }
                }
            }

        }

        }



}
