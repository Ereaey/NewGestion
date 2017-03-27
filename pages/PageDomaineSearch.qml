import QtQuick 2.8
import QtQuick.Controls 2.1
import QtQuick.Window 2.0
import Qt.labs.platform 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.0
import "qrc:/mycomponent"

Item {
    function showDomaine(idd)
    {
        var iddomaineespace = idd.substring(0, 4) + " " + idd.substring(4, 7) + " " + idd.substring(7, 10);
        return iddomaineespace;
    }

    FileDialog {
        id: fileSave
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            console.log("You chose: " + fileSave.file)
            treatment.exportPlan(treatment.selectDomaine.id, fileSave.file)
        }
        onRejected: {
            console.log("Canceled")
        }
        fileMode: FileDialog.SaveFile
        nameFilters: [ "html(*.html)" ]
        //Component.onCompleted: visible = true
    }
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
            text:"Recherche d'un domaine"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

        }
        /*
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
        }*/
    }

    Rectangle
    {
        //id:dataDomaine
        width: parent.width - 100
        height: t2.height + 20

        color: "#181A29"
        y:85
        x:50
        radius: 5
        ButtonSt
        {
            x:parent.width - 110
            text: "Rechercher"
            height:25
            y:6
            onClicked:
            {
                treatment.searchDomaine(idDomaine.text);
            }
        }
        Column
        {
            id:t2
            x:20
            y:10
            spacing: 5
            Text
            {
                text:"Identifiant du domaine : "
                color:"white"
                font.pointSize: 12
                TextField {
                    id:idDomaine
                    x:200
                    height: 25
                    y:-3
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
        }
    }

    Rectangle
    {
        id:dataDomaine
        width: parent.width - 100
        height: t.height + 20

        color: "#181A29"
        y:t2.height + 20+95
        x:50
        radius: 5
        visible:treatment.domaineexist

        ButtonSt
        {
            x:parent.width - 110
            text: "Exporter plan"
            height:25
            y:10
            onClicked:
            {
                fileSave.open();
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
            /*
            Text
            {
                text:"Attention le responsable n'appartient plus à la communauté"
                color:"red"
                font.pointSize: 10
            }*/
            Text
            {
                text:"Nom du domaine : "  + treatment.selectDomaine.nom
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Identifiant : " + showDomaine(treatment.selectDomaine.id)
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Responsable : " + treatment.selectDomaine.responsable
                color:"white"
                font.pointSize: 10
            }

            Text
            {
                text:"Nombre total de sous-domaines dans l'arborescence : " + treatment.selectDomaine.nbEnfant
                color:"white"
                font.pointSize: 10
            }
            Text
            {
                text:"Nombre de documents : " + treatment.selectDomaine.nbDocument
                color:"white"
                font.pointSize: 10
            }

        }
    }
/*
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
                    text:"Nom du document : " + model.data + "  (" + model.ide + ")"
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Nom du propriétaire : " + model.ide
                    font.pointSize: 8
                    x:10
                    y:23
                }
            }

        }
    }*/


}
