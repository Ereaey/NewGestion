import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/mycomponent"
Item {
    id:mainview
    property string valueUser: ""
    Timer
    {
        interval: 500;
        running: true;
        repeat: true
        onTriggered:
        {
            if (valueUser != idUser12.text && idUser12.length > 3)
            {
                valueUser = idUser12.text
                users.searchUser(idUser12.text);

            }
        }
    }
    Popup {
        id: chooseUser
        x: tree.visible ?  mainWin.width/2 - width/2  - tree.width : mainWin.width/2 - width/2
        y: 100
        width: 700
        height: idUser12.length < 3 ? 75 : parent.height - 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background:Rectangle
        {
            color: "#181A29"
            border.width : 2
            border.color: "white"
        }
        Rectangle
        {
            width:600
            height: 35
            x:40
            radius: 3
            color: "#364150"
            y:10
            Text
            {
                text:"Recherche via identifiant : "
                color:"white"
                font.pointSize: 10
                width: 200
                height: 25
                y:8
                x:15
            }
            TextField {
                id:idUser12
                x:280
                height: 25
                y:5
                width: 295
                placeholderText: qsTr("")
                color: "black"
                background: Rectangle {
                    implicitWidth: 150
                    implicitHeight: 20

                    opacity: enabled ? 1 : 0.3
                    border.color: idUser12.pressed ? "#26282a" : "#353637"
                    border.width: 1

                    radius:3
                }
            }
        }
        ListView
        {
            ScrollBar.vertical: ScrollBar{active: true}
            y:100
            x:5
            clip: true
            spacing: 10
            maximumFlickVelocity: 600
            highlightMoveVelocity : 600
            width:parent.width - 15
            height:parent.height - 110
            //id:autoCompletList
            model: users.result
            delegate: Rectangle
            {
                width: parent.width - 20
                x:10
                height: 40
                radius: 3
                color: "#364150"
                y:40
                Text
                {
                    color: "white"
                    text: model.modelData.nom + " " + model.modelData.id
                    font.pointSize: 10
                    x:10
                    y:5
                    width: parent.width - 190
                    height: 40
                    wrapMode: Text.WrapAnywhere

                }
                ButtonSt
                {
                    x:parent.width - 170
                    text: "Selectionner"
                    width: 160
                    height:30
                    y:5
                    onClicked:
                    {
                        chooseUser.close();
                        treatment.searchUserId(model.modelData.id, visuTree.currentIndex);
                    }
                }
            }

        }

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
                    if (swipeView.depth === 0)
                        swipeView.replace("qrc:MainMenu.qml", StackView.Immediate);
                    else
                        swipeView.pop(StackView.Immediate);
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
                chooseUser.open();
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
                text:"Nom Prenom : " + treatment.selectUser.nom
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Identifiant : " + treatment.selectUser.id
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de documents : " + treatment.selectUser.nbDocument
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de domaines responsable : " + treatment.selectUser.nbDomainesResp
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombres de domaines gestionnaire : " + treatment.selectUser.nbDomainesGest
                color:"white"
                font.pointSize: 10
            }


            Text
            {
                text: treatment.selectUser.abs
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
            width: parent.width - 40
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
            onCurrentIndexChanged:
            {
                treatment.searchUserId(treatment.selectUser.id, visuTree.currentIndex)
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
            text:"Liste des domaines séléctionnés"
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
                listDomaine.clear();
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
                fileSave.open();
            }
        }
        ButtonSt
        {
            x:parent.width - 350
            text: "Tout copier"
            height:20
            y:10
            onClicked:
            {
                listDomaine.allCopy();
            }
        }

        ListView
        {
            ScrollBar.vertical: ScrollBar{active: true}
            clip: true
            spacing: 10
            maximumFlickVelocity: 100
            width:parent.width - 15
            height:parent.height - 70
            y:50
            x:5
            id:aze
            model: listDomaine.domaines
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
                    text:"Nom du domaine : " + model.modelData.nom
                    font.pointSize: 10
                    x:10
                    y:5
                    id:idDomaine
                }
                Text
                {
                    color: "white"
                    text:"Id du domaine : " + model.modelData.iddomaine
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x: parent.width - 220
                    text: "Copier"
                    height:30
                    y:5
                    onClicked:
                    {
                        listDomaine.copy(model.modelData.iddomaine);
                    }
                }
                ButtonSt
                {
                    x: parent.width - 110
                    text: "Retirer"
                    height:30
                    y:5
                    onClicked:
                    {
                        listDomaine.deleteDomaine(model.modelData.iddomaine);
                    }
                }
            }

        }
    }


}
