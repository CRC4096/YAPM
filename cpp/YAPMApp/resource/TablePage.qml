
import QtQuick 2.7
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11

import YAPM.PwrMsrWrapper 1.0


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

    MeasurementDialog {
        id: measurementsDialog
    }
    //    highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
    Menu {
        id: dataMenu
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        modal: true

        Label {
            padding: 10
            font.bold: true
            width: parent.width
            horizontalAlignment: Qt.AlignHCenter
            text: qsTr("Change Entry of row " + currentIndex)
        }
        MenuItem {
            text: qsTr("Edit...")
            onTriggered: {
                console.log("Editing triggered. Index: " + currentIndex);
                measurementsDialog.editMeasurement(currentIndex, listView.model.get(currentIndex));

            }
        }
        MenuItem {
            text: qsTr("Remove")
            onTriggered: {
                console.log("Remove triggered. Index: " + currentIndex);
                listView.model.remove(currentIndex);
            }
        }
    }

    delegate: ItemDelegate {
        id: delegate
        width: listView.width

        checkable: true

        onPressAndHold: {
            console.log("Triggered Item delage. Current Index: " + index)
            listView.currentIndex = index;
            dataMenu.open()
        }

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

    model: PwrMsrWrapper.model

    ScrollBar.vertical: ScrollBar { }
}

