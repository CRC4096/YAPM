import QtQuick 2.7
import QtQuick.Controls 2.1

Dialog {
    id: measDialog

//    signal finished(string fullName, string address, string city, string number)

    function createMeasurement() {
//        form.valueField.text = ""
//        dialog.title = qsTr("Add Measurement");
        measDialog.open();
    }

//    x: parent.width / 2 - width / 2
//    y: parent.height / 2 - height / 2

    focus: true
    modal: true
    title: qsTr("Add Measurement")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: MeasurementDialogForm {
//        id: form
    }

//    onAccepted: finished(form.fullName.text, form.address.text, form.city.text, form.number.text)
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
