import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

ApplicationWindow {
    width: 600
    height: 300
    title: qsTr("Gestion des communautés")
    visible:true
    id:mainWin
    flags: Qt.Window | Qt.FramelessWindowHint

    Popup {
        id: chooseCommu
        x: parent.width/2 - width/2
        y: 100
        width: 700
        height: parent.height - 200
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside
        background:Rectangle
        {
            color: "#181A29"
            border.width : 2
            border.color: "white"
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
        //id:autoCompletList
        model: treatment.commu
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
                text: model.modelData.nom
                font.pointSize: 10
                x:10
                y:5
                id:ndDomaine
                width: parent.width - 20
                wrapMode: Text.WordWrap
                height: 40
            }
            Text
            {
                color: "white"
                text:"Résultat : " + model.modelData.result
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
                    chooseCommu.open();
                }
            }
        }

    }
    }

    Loader
    {
        anchors.fill: parent
        id: mainLoader
        source: "mainLoading.qml"

    }

    background:Rectangle
    {
        color: "#25273C"
    }

    header:    Rectangle
    {
        visible:false
        id:headerBar
        width: parent.width
        height: 30
        x:0
        y:0
        color: "#181A29"
        Text
        {
            id:nameCommu
            y:5
            x:parent.width - width - 120
            text:treatment.currentCommu
            color: "white"
            font.family: "Arial"
            font.pointSize: 12
            //width: parent.width - 20
            //x:parent.width/2-width/2
            ButtonSt
            {
                x:parent.width+10
                text: "Modifier"
                height:20
                onClicked:
                {
                    chooseCommu.open();
                    loading.load();
                }
            }
        }
    }



}
