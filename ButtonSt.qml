import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4

Button
{
    id:control4
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 20

        opacity: enabled ? 1 : 0.3
        color: control4.pressed ? (control4.highlighted ? "#585a5c" : "#e4e4e4") : (control4.highlighted ? "#353637" : "#f6f6f6")
        border.color: control4.pressed ? "#26282a" : "#353637"
        border.width: 1

        radius:3
    }
    contentItem: Text {
        width: control4.availableWidth
        height: control4.availableHeight
        text: control4.text
        opacity: enabled || highlighted ? 1 : 0.3
        color: control4.highlighted ? "#ffffff" : (control4.pressed ? "#26282a" : "#353637")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }
    onClicked:
    {
        chooseCommu.open();
    }
}
