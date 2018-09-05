import QtQuick 2.9
import QtQml 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.2

ApplicationWindow {
    id: window
    minimumHeight: 640
    minimumWidth: 480
    visible: true
    title: ""

    Material.theme: Material.Dark
    //    Material.accent: Material.BlueGrey
    //    Material.primary:

    Loader {
        anchors.fill: parent
        //        anchors.top: parent.top
        //        anchors.left: parent.left
        //        anchors.right: parent.right

        id: pageLoader
        source: "/forms/Dashboard.qml"
    }

    header: ToolBar {


        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                icon.name: "drawer"
                onClicked:  drawer.open()
            }

            Label {
                id: titleLabel
                text: "Yet Another Power Manager"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                icon.name: "menu"
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        text: "About"
                        onTriggered: aboutDialog.open()
                    }
                }
            }
        }
    }

    Drawer {
        id: drawer
        width: Math.min(window.width, window.height) / 3 * 2
        height: window.height
        interactive: true

        ListView {
            id: listView

            focus: true
            currentIndex: 0
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    pageLoader.source = model.source
                    drawer.close()
                }
            }

            model: ListModel {
                ListElement { title: "Dashboard"; source: "/forms/Dashboard.qml" }
                ListElement { title: "Daten"; source: "/forms/TablePage.qml" }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    Connections
    {
        target: measurementsDialog
        onFinished: {
            console.log("Acceppted MeasurementDialog")
            var tempSource = pageLoader.source
            pageLoader.source = "" //reload loader
            pageLoader.source = tempSource
        }
    }


    RoundButton {
        text: qsTr("+")
        highlighted: true
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            measurementsDialog.createMeasurement()
            console.log("Opening MeasurementDialog")
            //reloading of the page happens at the connection above
        }
    }


    MeasurementDialog {
        id: measurementsDialog
    }

    Dialog {
        id: aboutDialog
        modal: true
        focus: true
        title: "About"
        x: (window.width - width) / 2
        y: window.height / 6
        width: Math.min(window.width, window.height) / 3 * 2
        contentHeight: aboutColumn.height

        Column {
            id: aboutColumn
            spacing: 20

            Label {
                width: aboutDialog.availableWidth
                text: "The Qt Quick Controls 2 module delivers the next generation user interface controls based on Qt Quick."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }

            Label {
                width: aboutDialog.availableWidth
                text: "In comparison to the desktop-oriented Qt Quick Controls 1, Qt Quick Controls 2 "
                      + "are an order of magnitude simpler, lighter and faster, and are primarily targeted "
                      + "towards embedded and mobile platforms."
                wrapMode: Label.Wrap
                font.pixelSize: 12
            }
        }
    }

}

