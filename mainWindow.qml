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
        width: 600
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
            y:5
            x:parent.width - width - 120
            text:"Support assurane qualité opérationnel sites industriels valenciennes sevelnord et douvrin - FM"
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
