import QtQuick 2.4
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.4

Item {
    id: item1

    property alias valueField: valueField
    property alias calender: calender

    Label {
        id: valueLabel
        text: qsTr("Verbrauch")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 10
    }

    TextField {
        id: valueField
        placeholderText: "type in consumption"
        inputMask: "00000 \\k\\W\\h"
        width: 200
        text: " 0 kWh"
        anchors.verticalCenter: valueLabel.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 20
    }

    Calendar {
        id: calender
        anchors.top: valueLabel.bottom
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
