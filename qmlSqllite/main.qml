import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.1
import QtQuick.LocalStorage 2.0


ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    //Veritabanı Name
    property string dbID: "registerDB"

    //Veritabanı Version Number
    property string dbVersion: "1.0"

    //Veritabanı açıklaması
    property string dbDescription: "Database application"

    //Tahmini Veritabanı boyutu
    property int dbSize: 100000

    //Db
    property var db

    //constructor
    Component.onCompleted: {
        // Veritabanı nesnesi örneğini oluşturur(Opening)
        db = LocalStorage.openDatabaseSync(dbID,dbVersion,dbDescription,dbSize)

        //Create Table
        db.transaction(function(tx){
           var sqlquery = '(CREATE TABLE IF NOT EXISTS PRODUCTS'
                          + 'ID INTEGER PRIMARY KEY AUTOINCREMENT,'
                          + 'NAME TEXT NOT NULL,'
                          + 'WEIGHT INTEGER,'
                          + 'PRICE REAL,'
                          + 'BARCODE TEXT,'
                          + 'ABOUT TEXT)';
            tx.executeSql(sqlquery);
        });
        //Select From commend
        db.transaction(function(tx){

            var sqlquery = "SELECT * FROM PRODUCTS";
            var sqlquerydata = tx.executeSql(sqlquery);

            var ID;
            var NAME;
            var WEIGHT;
            var PRICE;
            var BARCODE;
            var ABOUT;
            var ix;

            for(ix =0;ix<sqlquerydata.rows.lenght; ++ix){
                myID = sqlquerydata.rows.item(ix).ID
                myNAME = sqlquerydata.rows.item(ix).NAME;
                myWEIGHT = sqlquerydata.rows.item(ix).WEIGHT;
                myPRICE = sqlquerydata.rows.item(ix).PRICE;
                myBARCODE = sqlquerydata.rows.item(ix).BARCODE;
                myABOUT = sqlquerydata.rows.item(ix).ABOUT;

                productListView.model.append({

                    ID: myID,
                    NAME: myNAME,
                    WEIGHT: myWEIGHT,
                    PRICE: myPRICE,
                    BARCODE: myBARCODE,
                    ABOUT: myABOUT
                });
            }

        });
    }

    StackView {
        id:stackView
        initialItem: DataForm
    }
    Component {
        id: dataForm
        DataForm {}
    }
    Component {
        id: inputForm
        InputForm{}
    }


}
















