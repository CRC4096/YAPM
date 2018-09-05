import QtQuick 2.7
import QtQuick.Controls 2.1

import YAPM.PwrMsrWrapper 1.0

Dialog {
    id: measDialog
    width: 400
    height: 400

    signal finished()

    function createMeasurement() {
        form.valueField.text = ""
        measDialog.title = qsTr("Add Measurement");
        measDialog.open();
    }

    x: parent.width / 2 - width / 2
    y: parent.height / 2 - height / 2

    focus: true
    modal: true
    title: qsTr("Add Measurement")
    standardButtons: Dialog.Ok | Dialog.Cancel

    contentItem: MeasurementDialogForm {
        id: form
    }

    onAccepted: {
        var consumption = form.valueField.text
        var dateString = form.calender.selectedDate
        PwrMsrWrapper.model.append(dateString, consumption)
        finished()
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
