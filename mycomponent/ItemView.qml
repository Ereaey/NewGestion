import QtQuick 2.6

import QtQuick.Layouts 1.1


Row{
    id: itemView
    x:2
    //clip: true
    Image
    {
        width: 15
        height: 15
        x:3
        y:4
        source:
        {
            modelData.hasChild? modelData.isOpen ? "qrc:/images/down-arrow.png" : "qrc:/images/previous.png" : ""
        }
        MouseArea{
            anchors.fill: parent
            onClicked:
            {
                modelData.isOpen = !modelData.isOpen;
            }
        }
    }
    Column{
        x:3
        y:1
        Row
        {
            //clip: true
        Rectangle
        {
            height:15
            width: 5
            color: "transparent"
        }
        Text{
            clip: true
            width: 300
            text: modelData.content
            font.pointSize: 10
            font.family: "Helvetica"
            color: modelData.isSelect ? "#FFC53C" : "white"
            MouseArea{
                anchors.fill: parent
                onClicked:
                {
                    console.log(modelData.content)
                    listDomaine.addDomaine(modelData.content, modelData.id);
                }
            }
        }
        Rectangle
        {
            height:15
            width: 5
            color: "transparent"
        }
        }
        Loader{
            x:7
            y:8
            source: modelData.isOpen ? "TreeItemsList.qml" : "Empty.qml"
        }
    }

}
