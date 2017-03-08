
import "qrc:/mycomponent"


import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import Qt.labs.platform 1.0
import QtQuick.Controls.Styles 1.4

Item {
    FileDialog {
        id: fileSave
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileSave.fileUrls)
            listDomaine.exportList(fileSave.fileUrls);
        }
        onRejected: {
            console.log("Canceled")
        }

        fileMode: FileDialog.SaveFile
        nameFilters: [ "CSV(*.csv)" ]
        //Component.onCompleted: visible = true
    }
    id:mainview2
    property string valueGoal: ""
    Timer
    {
        interval: 500;
        running: true;
        repeat: true
        onTriggered:
        {
            if (valueGoal != idGoal.text && idGoal.length > 3)
            {
                valueGoal = idGoal.text
                goals.search(idGoal.text);

            }
        }
    }
    Popup {
        id: chooseGoal
        x: tree.visible ?  mainWin.width/2 - width/2  - tree.width : mainWin.width/2 - width/2
        y: 100
        width: 700
        height: idGoal.length < 3 ? 75 : parent.height - 200
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
                id:idGoal
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
                    border.color: idDocument.pressed ? "#26282a" : "#353637"
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
            model: goals.result
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
                    text: modelData
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
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
                        chooseGoal.close();
                        treatment.searchGoal(modelData, true, true, false);
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
                    swipeView.replace("qrc:MainMenu.qml", StackView.Immediate);
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
                 chooseGoal.open();
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
            text:"Goal en cours de recherche : " + treatment.goal
            x:20
            y:10
            color:"white"
            font.pointSize: 12
        }

    /*
        Text
        {
            text:"Nombres de domaines : 1204"
            x:20
            y:33
            color:"white"
            font.pointSize: 10
        }*/
        Text
        {
            text:"Modes de recherche :"
            x:20
            y:41
            color:"white"
            font.pointSize: 10
        }
        Text
        {
            text:"Modificateur et Lecteur"
            x:180
            y:42
            color:"red"
            font.pointSize: 10
        }
    /*
        Text
        {
            text:"Responsable"
            x:280
            y:42
            color:"blue"
            font.pointSize: 10
        }/*
        Text
        {
            text:"Lecteur"
            x:380
            y:42
            color:"green"
            font.pointSize: 10
        }*/
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
