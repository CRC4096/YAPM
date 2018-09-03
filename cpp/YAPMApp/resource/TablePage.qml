
import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import PowerMeasurementModel 1.0


ListView {
    id: listView
    anchors.fill: parent

    //    signal pressAndHold(int index)

    focus: true
    boundsBehavior: Flickable.DragOverBounds

    //    section.property: "Zeit"
    //    section.criteria: ViewSection.FullString
    //    section.delegate: ToolBar {
    //        id: background

    //        Label {
    //            id: label
    //            text: section
    //            anchors.fill: parent
    //            horizontalAlignment: Qt.AlignHCenter
    //            verticalAlignment: Qt.AlignVCenter
    //        }
    //    }

    header:
        Rectangle {
        width: listView.width
        height: timeHeader.font.pixelSize + 10
        color: "transparent"

        Label {
            id: timeHeader
            width: parent.width*0.5
            anchors.left: parent.left
            anchors.leftMargin: 10

            text: qsTr("Datum")
            font.weight: Font.ExtraBold
            font.pixelSize: 20
            elide: Text.ElideRight

            horizontalAlignment: "AlignLeft"
            verticalAlignment: "AlignVCenter"
        }

        Label {
            id: valueHeader
            width: parent.width*0.5
            anchors.right: parent.right
            anchors.rightMargin: 15
            text: qsTr("Messung")
            font.weight: Font.ExtraBold
            font.pixelSize: 20
            elide: Text.ElideRight

            horizontalAlignment: "AlignRight"
            verticalAlignment: "AlignVCenter"
        }

    }

//    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }

    delegate: ItemDelegate {
        id: delegate
        width: listView.width

        checkable: true

        contentItem:
            RowLayout {
            spacing: 10

            Label {
                id: timeLabel
                width: parent.width*0.5
                text: Zeit
                font.weight: Font.ExtraLight
                elide: Text.ElideRight
                Layout.fillWidth: true

                horizontalAlignment: "AlignLeft"
            }

            Label {
                id: valueLabel
                width: parent.width*0.5
                text: Messung + " kWh"
                font.weight: Font.ExtraLight
                elide: Text.ElideRight
                Layout.fillWidth: true

                horizontalAlignment: "AlignRight"
            }


        }
        //        Connections {
        //            target: delegate
        //            onPressAndHold: listView.pressAndHold(index)
        //        }
    }

    model: PowerMeasurementModel {
        id: model
    }

    ScrollBar.vertical: ScrollBar { }
}

