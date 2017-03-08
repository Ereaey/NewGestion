import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "qrc:/mycomponent"

Item {
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
            text:"Recherche d'un document"
            x:parent.width/2 - width/2
            y:10
            color:"white"
            font.pointSize: 16

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
            width: parent.width - 40
            Text
            {
                text:"Documents en cours de recherche"
                color:"white"
                font.pointSize: 12
                 height: 25
            }
            Text
            {
                text:"Recherche via identifiant : "
                color:"white"
                font.pointSize: 10
                width: parent.width
                height: 25
                TextField {
                    id:idDocument
                    x:200
                    height: 25
                    y:-5
                    width: 300
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
            }/*
            Text
            {
                height: 25
                text:"Confidentialité : "
                color:"white"
                font.pointSize: 10
                ComboBox {
                    x:200
                    y:-5
                    width: 300
                    height: 25
                    id:confDocument
                    model: [ "C1", "C2", "C3", "C4" ]
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 20

                        opacity: enabled ? 1 : 0.3
                        border.color: confDocument.pressed ? "#26282a" : "#353637"
                        border.width: 1

                        radius:3
                    }


                }
            }
            Text
            {
                height: 25
                text:"Statut : "
                color:"white"
                font.pointSize: 10
                ComboBox {
                    x:200
                    y:-5
                    width: 300
                    height: 25
                    id:statutDocument
                    model: [ "Publié", "De travail"]
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 20

                        opacity: enabled ? 1 : 0.3
                        border.color: statutDocument.pressed ? "#26282a" : "#353637"
                        border.width: 1

                        radius:3
                    }


                }
            }
            Text
            {
                height: 25
                text:"Date de derniére modification : "
                color:"white"
                font.pointSize: 10
                TextField {
                    id:dateDocument
                    x:200
                    height: 25
                    y:-5
                    placeholderText: qsTr("")
                    color: "black"
                    width: 300
                    background: Rectangle {
                        implicitWidth: 150
                        implicitHeight: 20

                        opacity: enabled ? 1 : 0.3
                        border.color: dateDocument.pressed ? "#26282a" : "#353637"
                        border.width: 1

                        radius:3
                    }
                }
            }*//*
            Text
            {
                height: 25
                text:"Avec plus de x piéces jointes: "
                color:"white"
                font.pointSize: 10
                TextField {
                    id:nbPjDocument
                    x:200
                    height: 25
                    y:-5
                    placeholderText: qsTr("")
                    color: "black"
                    width: 300
                    background: Rectangle {
                        implicitWidth: 150
                        implicitHeight: 20

                        opacity: enabled ? 1 : 0.3
                        border.color: nbPjDocument.pressed ? "#26282a" : "#353637"
                        border.width: 1

                        radius:3
                    }
                }
            }
            Text
            {
                height: 25
                text:"Option supplémentaires : "
                color:"white"
                font.pointSize: 10
                width: parent.width
                Column {
                    x:195
                    height: 60
                    y:-5
                    width: parent.width

                    CheckBox {
                        id:control
                        text: qsTr("Propriétaire inconnu")
                        checked: false
                        indicator: Rectangle {
                            implicitWidth: 26
                            implicitHeight: 26
                            x: control.leftPadding
                            y: 0
                            radius: 3
                            border.color: control.down ? "gray" : "gray"

                            Rectangle {
                                width: 14
                                height: 14
                                x: 6
                                y: 6
                                radius: 2
                                color: control.down ? "gray" : "gray"
                                visible: control.checked
                            }
                        }

                        contentItem: Text {
                            color: "white"
                            width:100
                            height: 20
                            text:control.text
                            horizontalAlignment: Text.AlignHCenter
                            //verticalAlignment: Text.AlignVCenter
                            leftPadding: control.indicator.width + 30
                            font.pointSize: 10
                            y:-20
                        }

                        width: 150
                    }
                    CheckBox {
                        id:videDocument
                        text: qsTr("Documents vide")
                        checked: false

                        indicator: Rectangle {
                            implicitWidth: 26
                            implicitHeight: 26
                            x: videDocument.leftPadding
                            y: 0
                            radius: 3
                            border.color: videDocument.down ? "gray" : "gray"

                            Rectangle {
                                width: 14
                                height: 14
                                x: 6
                                y: 6
                                radius: 2
                                color: videDocument.down ? "gray" : "gray"
                                visible: videDocument.checked
                            }
                        }

                        contentItem: Text {
                            color: "white"
                            width:100
                            height: 20
                            text:videDocument.text
                            //horizontalAlignment: Text.AlignHCenter
                            //verticalAlignment: Text.AlignVCenter
                            leftPadding: videDocument.indicator.width + 5
                            font.pointSize: 10
                            y:-20
                        }

                        width: 150
                    }
                }
            }*/

            Rectangle
            {
                width: parent.width
                height: 30
                color: "transparent"
                ButtonSt
                {
                    x:parent.width - 100
                    text:"Rechercher"
                    onClicked:
                    {
                        treatment.searchDocument(idDocument.text);
                    }
                }
                ButtonSt
                {
                    x:parent.width - 210
                    text:"Vider"
                }
            }

        }
    }

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
            model: treatment.listDoc
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
                    text:"Nom du document : " + model.modelData.nom + "("+ model.modelData.id +")"
                    font.pointSize: 10
                    x:10
                    y:5
                    id:ndDomaine
                }
                Text
                {
                    color: "white"
                    text:"Nom du propriétaire : " + model.modelData.proprio
                    font.pointSize: 8
                    x:10
                    y:23
                }
                ButtonSt
                {
                    x:parent.width - 110
                    text: "Voir le domaine"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchDomaine(model.modelData.iddomaine);
                        swipeView.replace("qrc:pages/PageDomaineSearch.qml", StackView.Immediate);
                    }
                }
                ButtonSt
                {
                    x:parent.width - 220
                    text: "Voir propriétaire"
                    height:30
                    y:5
                    onClicked:
                    {
                        treatment.searchUserId(model.modelData.idproprio);
                        swipeView.replace("qrc:pages/PageUtilisateurSearch.qml", StackView.Immediate);
                    }
                }
            }

        }
    }


}
