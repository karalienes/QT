#include "sqldataprocessing.h"

Sqldataprocessing::Sqldataprocessing()
{
    db = new QSqlDatabase();
    init();

}

Sqldataprocessing::~Sqldataprocessing()
{

}

void Sqldataprocessing::init()
{
   *db= QSqlDatabase::addDatabase("QSQLITE");
    db->setDatabaseName("registerDB.db");
    if (!db->open()) {
        qDebug()<<"Not opening!";

    }
    else{
        qDebug()<<"Db opening!";
    }
}

void Sqldataprocessing::createQuery(QString tablename,QStringList datalist)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString testTableQuery = "CREATE TABLE IF NOT EXISTS"+ tablename +
                             "( TEST_ID = :TEST_ID  INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                             "  TEST_NAME = :TEST_NAME  TEXT NOT NULL,  "
                             "  TEST_LAST_NAME =:TEST_NAME  TEXT)";

    query.bindValue(":TEST_ID", datalist[0]);
    query.bindValue(":TEST_NAME", datalist[1]);
    query.bindValue(":TEST_LAST_NAME", datalist[2]);

    query.prepare(testTableQuery);


    if (!query.exec())
        qDebug()
                << "DataBaseController::createTables::Test: Create table error: "
                        + query.lastError().text();
    else{
        qDebug()<<"Database is opening and processing successfully";
    }
    db.close();

}

void Sqldataprocessing::readQuery(QString tablename)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    QString testTableQuery = QString("SELECT * FROM "+tablename);
    qDebug()<<testTableQuery;
//    query.bindValue(":Tablename", username);
    query.prepare(testTableQuery);
    if (!query.exec())
        qDebug()
                << "DataBaseController::ReadTableData::Test: :Read Datas errors: "
                        + query.lastError().text();
    else{
        qDebug()<<"Database is opening and processing successfully";

        while(query.next()){
            datasetstruct = new dataset;
            QString dat1 =query.value(0).toString();
            QString dat2 =query.value(1).toString();
            QString dat3 =query.value(2).toString();
            QString dat4 =query.value(3).toString();
            QString dat5 =query.value(4).toString();
            QString dat6 =query.value(5).toString();
            //qDebug()<<dat1 <<"--"<<dat2<<"--"<<dat3<<"--"<<dat4<<"--"<<dat5<<"--"<<dat6;

            datasetstruct->ID = dat1.toInt();
            datasetstruct->NAME = dat2;
            datasetstruct->WEIGHT = dat3.toInt();
            datasetstruct->PRICE = dat4.toFloat();
            datasetstruct->BARCODE = dat5;
            datasetstruct->ABOUT = dat6;
            datasetvec.push_back(*datasetstruct);



            unsigned int vecSize = datasetvec.size();

            // run for loop from 0 to vecSize
            for(unsigned int i = 0; i < vecSize; i++)
            {
              qDebug()<<"*************************************************";
              qDebug() << datasetvec[i].ID << ": ID ";
              qDebug() << datasetvec[i].NAME << ": NAME ";
              qDebug() << datasetvec[i].WEIGHT << ": WEIGHT ";
              qDebug() << datasetvec[i].PRICE << ": PRICE ";
              qDebug() << datasetvec[i].BARCODE << ": BARCODE ";
              qDebug() << datasetvec[i].ABOUT << ": ABOUT ";
              qDebug()<<"*************************************************";
            }

            delete datasetstruct;
        }

    }
    db.close();

}

void Sqldataprocessing::updateQuery(QString tablename,QStringList datalist)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    QString testTableQuery = "UPDATE "+ tablename +" SET "
                            "ID= :ID,"
                            "NAME = :NAME,"
                            "WEIGHT = :WEIGHT,"
                            "PRICE = :PRICE,"
                            "BARCODE = :BARCODE,"
                            "ABOUT = :ABOUT"
                            "WHERE ID = :ID";

    query.bindValue(":ID",datalist[0]);
    query.bindValue(":NAME",datalist[1]);
    query.bindValue(":WEIGHT",datalist[2]);
    query.bindValue(":PRICE",datalist[3]);
    query.bindValue(":BARCODE",datalist[4]);
    query.bindValue(":ABOUT",datalist[5]);

    query.prepare(testTableQuery);
    if (!query.exec())
        qDebug()
                << "DataBaseController::ReadTableData::Test: :Update Data errors: "
                        + query.lastError().text();
    else{
        qDebug()<<"Database is opening and processing successfully";
    }
    db.close();


}

void Sqldataprocessing::deleteQuery(QString tablename,QStringList datalist)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    QString testTableQuery = "DELETE FROM "+ tablename +"SET "
                             "WHERE ID = :ID";
    query.bindValue(":ID",datalist[0]);

    query.prepare(testTableQuery);
    if (!query.exec())
        qDebug()
                << "DataBaseController::ReadTableData::Test: :Delete Data errors: "
                        + query.lastError().text();
    else{
        qDebug()<<"Database is opening and processing successfully";
    }
    db.close();
}

void Sqldataprocessing::InsertQuery(QString tablename,QStringList datalist)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;

    QString testTableQuery = "INSERT INTO " + tablename +
                             "(ID,NAME,WEIGHT,PRICE,BARCODE,ABOUT) "
                             "VALUES(:ID,:NAME,:WEIGHT,:PRICE,:BARCODE,:ABOUT)";

    query.bindValue(":ID",datalist[0]);
    query.bindValue(":NAME",datalist[1]);
    query.bindValue(":WEIGHT",datalist[2]);
    query.bindValue(":PRICE",datalist[3]);
    query.bindValue(":BARCODE",datalist[4]);
    query.bindValue(":ABOUT",datalist[5]);

    query.prepare(testTableQuery);
    if (!query.exec())
        qDebug()
                << "DataBaseController::ReadTableData::Test: :Insert Into Data errors: "
                        + query.lastError().text();
    else{
        qDebug()<<"Database is opening and processing successfully";
    }
    db.close();
}










