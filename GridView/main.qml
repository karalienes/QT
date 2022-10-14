import QtQuick 2.6
import QtQuick.Controls 2.5
import QtQuick.Window 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("GridView")

    Component.onCompleted: {
        var colores = ['red','orange','green','blue','cyan','brown'];
        var ix;
        var jx;
        var colorcounter=1;
        for(jx=0;jx<20;++jx){

            for(ix=0 ;  ix<colores.length;ix++){
                gridView_test.model.append({myColor: colores[ix], myText: colorcounter});
                ++colorcounter;
            }

        }

//        gridView_test.model.append({myColor:'orange'});
//        gridView_test.model.append({myColor:'red'});
//        gridView_test.model.append({myColor:'blue'});
    }


    GridView {
        id: gridView_test

        anchors{
            top: parent.top
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            leftMargin: 20
            rightMargin: 20
            topMargin:  20

        }

        cellWidth: width/3
        cellHeight: height/3

        model: ListModel{}

        delegate: Rectangle {
            width: gridView_test.cellWidth
            height: gridView_test.cellHeight
            color: myColor


            Text{
                text: myText
                font.pointSize: 20
            }
        }
    }
}
