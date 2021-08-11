import QtQuick 2.6
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Adsb 1.0

Controls.Button {
    id: root

    AdsbController { id: controller }

    iconSource: "qrc:/icons/adsb.svg"
    tipText: qsTr("Adsb overview")
    highlighted: popup.visible
    onClicked: popup.visible ? popup.close() : popup.open()

    Component.onCompleted: {
        map.registerController("adsbController", controller)
        controller.start();
    }

    Controls.Popup {
        id: popup

        closePolicy: Controls.Popup.CloseOnPressOutsideParent
        width: Controls.Theme.baseSize * 10
        height: Math.min(implicitHeight, main.availableHeight)
        y: root.height + Controls.Theme.margins
        x: root.x

        Widgets.ListWrapper {
            model: controller.adsb
            anchors.fill: parent
            emptyText: qsTr("No ADS-B data")

            delegate: AdsbState {
                width: parent.width
                callsign: modelData.callsign
                originCountry: modelData.originCountry
            }
        }
    }
}

