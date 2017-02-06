import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

Item{
    id:windowLoad
    anchors.fill: parent

    Timer {
        interval: 10; running: true; repeat: false
        onTriggered:
        {
            loading.load();
        }
    }

    Timer
    {
        interval: 100; running: true; repeat: true
        onTriggered:
        {

            progressLoad.value = loading.progress / 100
            //console.log(progressLoad.value)
            //console.log(progressLoad.value, progressLoad.to)
            /*
            if (progressLoad.value + 0.1 >= 1.0)
            {
                console.log("Chargement terminé")
                mainWin.flags = Qt.Window
                mainLoader.source = "main.qml"
                mainWin.width = 800

                mainWin.height = 600
                headerBar.visible = true
                mainWin.showMaximized()
            }*/
        }
    }

    Image
    {
        source:"images/logo.png"
        //x:-100
       //y:-300
        y:-30
    }
    Image
    {
        source:"images/cross.png"
        //x:-100
       //y:-300
        y:-17
        x:parent.width - width - 10
        width: 20
        height: 20
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                Qt.quit()
            }
        }
    }

    /*
    Image
    {
        source:"images/load.gif"
        //x:-100
       //y:-300
        y:110
        x:parent.width/2 - width/2
    }
    */

    Text
    {
        //verticalAlignment: font.V
        color: "white"
        text: "Gestion des bases documentaires"
      //font.family: "Helvetica"
      font.pointSize: 16
      horizontalAlignment: Text.AlignHCenter
      width: parent.width
      y: 80
    }


    ProgressBar
    {
        id:progressLoad
        x:0
        y:230
        width: parent.width
        value:0.2
        //color: "#25273C"
        background: Rectangle {
            implicitWidth: 200
            implicitHeight: 2
            color: "#25273C"
            //radius: 3
        }

        contentItem: Item {
            implicitWidth: 200
            implicitHeight: 2

            Rectangle {
                width: progressLoad.visualPosition * parent.width
                height: parent.height
                radius: 2
                color: "#4f839c"
            }
        }
    }
    Text
    {
        color: "white"
        x:2
        y:238
        text:"Chargement des documents : 0 /1000"
    }
    Text
    {
        color: "white"
        x:2
        y:253
        text:"Chargement des fichiers : 1 / 5"
    }
}
