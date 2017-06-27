import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.0
import Qt.labs.platform 1.0
import "qrc:/mycomponent"

Item {
    id:mainview
    FileDialog {
        id: fileSavet
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileSavet.file)
            treatment.exportAllGoal(fileSavet.file);
        }
        onRejected: {
            console.log("Canceled")
        }

        fileMode: FileDialog.SaveFile
        nameFilters: [ "CSV(*.csv)" ]
        //Component.onCompleted: visible = true
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
            text:"Liste des goals"
            x:20
            y:10
            color:"white"
            font.pointSize: 12
        }
        ButtonSt
        {
            x:parent.width - 110
            text: "Exporter liste"
            visible: treatment.currentAction == "Rechercher les goals" ? true : false
            height:25
            y:10
            onClicked:
            {
                fileSavet.open();
            }
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
            model: treatment.listGoal
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
                    text:"Nom du goal : " + model.modelData.nom
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Id du goal : " + model.modelData.idgoal
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x:parent.width - 150
                    text: "Rechercher dans l'arbre"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchGoal(model.modelData.nom, true, true, false);
                        swipeView.replace("qrc:pages/PageGoalSearch.qml", StackView.Immediate);
                    }
                }
            }

        }

        }



}
