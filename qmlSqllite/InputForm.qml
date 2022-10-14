import QtQuick 2.0
import QtQuick.Controls 2.1
import QtQuick.LocalStorage 2.0

Item {
    anchors.fill: parent

    Column {
        spacing: 2

        Row {
            spacing: 2
            Label{
                text: "ID"
            }
            TextField {
                id: ıdtextfield
            }
        }
        Row {
            spacing: 2
            Label{
                text: "NAME"
            }
            TextField {
                id: nametextfield
            }
        }
        Row {
            spacing: 2
            Label{
                text: "WEIGHT"
            }
            TextField {
                id: weighttextfield
            }
        }
        Row {
            spacing: 2
            Label{
                text: "PRICE"
            }
            TextField {
                id: pricetextfield
            }
        }
        Row {
            spacing: 2
            Label{
                text: "BARCODE"
            }
            TextField {
                id: barcodetextfield
            }
        }
        Row {
            spacing: 2
            Label{
                text: "ABOUT"
            }
            TextField {
                id: abouttextfield
            }
        }

    }
}
