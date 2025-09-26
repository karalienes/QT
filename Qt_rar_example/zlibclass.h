#ifndef ZLIBCLASS_H
#define ZLIBCLASS_H

#include <QObject>
#include <QDebug>
#include <quazip/quazip.h>
#include <quazip/quazipfile.h>
#include <QFile>
#include <QFileInfo>
#include <QDir>

class zlibClass : public QObject
{
    Q_OBJECT
public:
    explicit zlibClass(QObject *parent = nullptr);
    void zipFiles(const QString& zipFilePath, const QStringList& filePaths);
    void unzipFiles(const QString & zipFilePath, const QString &extractDirPath);

signals:
};

#endif // ZLIBCLASS_H
