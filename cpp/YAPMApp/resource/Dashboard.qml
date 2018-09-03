import QtQuick 2.0
import QtQml 2.11
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.0
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.2

Item {

    Rectangle {
        id: dashboardcontent
        visible: true
        anchors.margins: 30
        //        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        height: 150


        color: "transparent"


        property int amountLines: 3
        property int lineHeight: 35
        property int lineWidth: overviewGroupBox.width

        GroupBox {
            id: overviewGroupBox
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: dashboardcontent.bottom

            title: qsTr("Übersicht")

            label: Rectangle {
                anchors.topMargin: 5
                anchors.bottom: parent.top
                anchors.bottomMargin: 5
                color: "transparent"                  //set this to the background color
                width: parent.width
                height: dashboardContentTitle.font.pixelSize
                Label {
                    id: dashboardContentTitle
                    text: qsTr("Übersicht")
                    anchors.left: parent.left
                    anchors.leftMargin: 10
                    font.weight: Font.DemiBold
                    font.pixelSize: 16
                    horizontalAlignment: Text.AlignLeft
                }
            }

            background: Item {
                Rectangle {
                    id: overviewGroupBoxBackground
                    y: overviewGroupBox.topPadding - overviewGroupBox.padding
                    width: parent.width
                    height: parent.height - overviewGroupBox.topPadding + overviewGroupBox.padding
                    color: "transparent"
                    border.color: Material.primary
                    radius: 4
                }

                DropShadow {
                    anchors.fill: overviewGroupBoxBackground
                    //                    horizontalOffset: 3
                    //                    verticalOffset: 3
                    radius: 5.0
                    samples: 34
                    //                color: "#aaFFFFFF"
                    source: overviewGroupBoxBackground
                }
            }


            DashboardLine{
                id: currentCunsumption
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5
                height: dashboardcontent.lineHeight;

                labelText:  qsTr("Last Measurment")
                labelValue: qsTr("1000 kWh")
                optionalComponent:
                    Component {
                    Label {
                        text: qsTr("from 01.09.2019")
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft

                    }
                }
            }

            DashboardLine{
                id: forecast
                anchors.top: currentCunsumption.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 5
                height: dashboardcontent.lineHeight;

                labelText:  qsTr("Forcast")
                labelValue: qsTr("3000 kWh")
            }


            DashboardLine{
                id: cunsumptionPerINterval
                anchors.top: forecast.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                //                anchors.bottom: parent.bottom;
                anchors.margins: 5
                height: dashboardcontent.lineHeight;

                labelText:  qsTr("Cunsumption per")
                labelValue: qsTr("25 kWh")
                optionalComponent:
                    Component {
                    ComboBox {
                        model: ["Day", "Week", "Month"]
                    }
                }
            }


        }
    }

}
