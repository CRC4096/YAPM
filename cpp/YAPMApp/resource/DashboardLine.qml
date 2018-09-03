import QtQuick 2.0
import QtQml 2.11
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
    id: item1
//    anchors.fill: parent

    property string labelText: "labelText"
    property string labelValue: "0"
    property var optionalComponent: Component{Item{}}

    Label {
        id: label
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.4
//        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft


        text: parent.labelText
    }

    Loader {
        id: optional
        anchors.top: parent.top
        anchors.left: label.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.3
//        height: parent.height
        sourceComponent: parent.optionalComponent
    }

    Label {
        id: value
        anchors.top: parent.top
        anchors.left: optional.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.3
//        height: parent.height
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight

        text: parent.labelValue

    }


}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
