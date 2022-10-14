import QtQuick 2.15
import QtQuick.Controls 2.1

Item {
    anchors.fill: parent
    ListView {
        id: productListView
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: buttonid.top
        }

        model: ListModel {}

        delegate: Label {
            anchors{
                left: parent.left
                right: parent.right
            }

            height: 50
            text: ID + '' +NAME + ''+ WEIGHT + " " + PRICE + " " + BARCODE + " " + ABOUT
        }

    }

    Button {
        id: buttonid

        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        onClicked: {

        }
    }
}
