import QtQuick 2.0

Item {
    width: 600
    height: 600

    Component.onCompleted: {
        myListView.model.append({myColor: 'red', myText: 'Enes'});
        myListView.model.append({myColor: 'blue', myText: 'Karali' });
        myListView.model.append({myColor: 'green' , myText: 'Dilek'});
        myListView.model.append({myColor: 'black', myText: 'Bakar'});
        myListView.model.append({myColor: 'red', myText: 'Enes'});
        myListView.model.append({myColor: 'blue', myText: 'Karali' });
        myListView.model.append({myColor: 'green' , myText: 'Dilek'});
        myListView.model.append({myColor: 'black', myText: 'Bakar'});
        myListView.model.append({myColor: 'red', myText: 'Enes'});
        myListView.model.append({myColor: 'blue', myText: 'Karali' });
        myListView.model.append({myColor: 'green' , myText: 'Dilek'});
        myListView.model.append({myColor: 'black', myText: 'Bakar'});


    }

    ListView{
        id: myListView
        anchors.fill: parent
        model: ListModel {}
        delegate: Rectangle {
            width: parent.width
            height: 50
            color: myColor
            Text {
                anchors.centerIn: parent
                color: "White"
                text: myText
                font.pointSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    mainWidget.printTextColor(myText);
                }
            }
        }
    }
}
