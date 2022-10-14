#ifndef SQLDATAPROCESSING_H
#define SQLDATAPROCESSING_H

#include <QSqlQuery>
#include <QtSql/QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Sqldataprocessing
{
public:

    struct dataset{
        int ID;
        QString NAME;
        int WEIGHT;
        float PRICE;
        QString BARCODE;
        QString ABOUT;
    };

    Sqldataprocessing();
   ~Sqldataprocessing();
    void init();
    void createQuery(QString tablename,QStringList datalist);
    void readQuery(QString tablename);
    void updateQuery(QString tablename,QStringList datalist);
    void deleteQuery(QString tablename,QStringList datalist);
    void InsertQuery(QString tablename,QStringList datalist);
    vector<dataset> datasetvec;
    dataset *datasetstruct;


private:
     QSqlDatabase *db;
};

#endif // SQLDATAPROCESSING_H
