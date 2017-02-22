import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
//import QtQuick.Controls.Styles 1.4
//import Qt.labs.controls 1.0

Row{
    id: itemView
    Image
    {
        width: 15
        height: 15
        x:3
        source:
        {
            modelData.hasChild? modelData.isOpen ? "down-arrow.png" : "right-arrow.png" : ""
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
        Rectangle
        {
            height:15
            width: 5
            color: "transparent"
        }
        Text{
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
            x:15
            y:8
            source: modelData.isOpen ? "TreeItemsList.qml" : "Empty.qml"
        }
    }

}
