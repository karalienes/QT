#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CreateJson(test);

}


void MainWindow::CreateJson(QStringList key, QString root, QString &path, QIODevice::OpenModeFlag device)
{
    QJsonObject jsonobj;

    for(int i=0;i<key.length();i++){
        jsonobj.insert(key[i],"");
    }

    QJsonObject content;
    content.insert( root, jsonobj );

    QJsonDocument document;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file( path );
    if( file.open( QIODevice::WriteOnly | device ) )
    {
        QTextStream iStream( &file );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        file.close();
    }
    else
    {
        cout << "file open failed: " << path.toStdString() << endl;
    }
}

void MainWindow::ReadJson(QString path)
{
    QFile file( path );
    if( file.open( QIODevice::ReadOnly ) )
    {
        QByteArray bytes = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            cout << "fromJson failed: " << jsonError.errorString().toStdString() << endl;
            return ;
        }
        if( document.isObject() )
        {
            QJsonObject jsonObj = document.object();
            QStringList books;
            books << "book1" << "book2";
            for( auto book: books )
            {
                if( jsonObj.contains( book ) )
                {
                    QJsonObject obj = jsonObj.value( book ).toObject();
                    QStringList keys = obj.keys();
                    for( auto key: keys )
                    {
                        auto value = obj.take( key );
                        if( value.isDouble() )
                        {
                            qDebug() << key << " : " << value.toDouble();
                        }
                        else if( value.isString() )
                        {
                            qDebug() << key << " : " << value.toString();
                        }

                    }
                }
            }
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

