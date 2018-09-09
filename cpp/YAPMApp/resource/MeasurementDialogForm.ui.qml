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
        width: 200
        placeholderText: "type in consumption"
        inputMask: ""
        text: ""
        horizontalAlignment: Text.AlignRight

        anchors.right: suffixField.left
        anchors.verticalCenter: valueLabel.verticalCenter
        anchors.rightMargin: 5
    }

    Label {
        id: suffixField
        text: "kWh"
        anchors.verticalCenter: valueField.verticalCenter
        anchors.left: valueField
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
    D{i:0;autoSize:true;height:480;width:640}D{i:2;anchors_width:200}
}
 ##^##*/
