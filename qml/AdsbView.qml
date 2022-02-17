import QtQuick 2.12
import Industrial.Controls 1.0 as Controls
import Industrial.Widgets 1.0 as Widgets
import Dreka.Adsb 1.0

Controls.Button {
    id: root

    AdsbController {
        id: controller
        centerPosition: map.centerPosition
    }

    Component.onCompleted: {
        map.registerController("adsbController", controller)
        controller.start();
    }

    iconSource: "qrc:/icons/adsb.svg"
    tipText: qsTr("Adsb overview")
    highlighted: sidebar.sourceComponent === adsbComponent
    onClicked: sidebar.sourceComponent = highlighted ? null : adsbComponent

    Component {
        id: adsbComponent

        Controls.Pane {
            width: Controls.Theme.baseSize * 10

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
}

