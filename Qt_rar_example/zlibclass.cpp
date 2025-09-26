#include "zlibclass.h"

zlibClass::zlibClass(QObject *parent)
    : QObject{parent}
{}

void zlibClass::zipFiles(const QString &zipFilePath, const QStringList &filePaths)
{
    QuaZip zip(zipFilePath);
    if (!zip.open(QuaZip::mdCreate)) {
        qWarning("Failed to create zip file");
        return;
    }

    foreach (const QString &filePath, filePaths) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("Failed to open file for reading");
            continue;
        }

        QuaZipFile zipFile(&zip);
        QuaZipNewInfo zipInfo(QFileInfo(filePath).fileName(), file.fileName());

        if (!zipFile.open(QIODevice::WriteOnly, zipInfo)) {
            qWarning("Failed to open file in zip archive for writing");
            continue;
        }

        zipFile.write(file.readAll());
        zipFile.close();
        file.close();
    }

    zip.close();
}

void zlibClass::unzipFiles(const QString &zipFilePath, const QString &extractDirPath)
{
    QuaZip zip(zipFilePath);
    if(!zip.open(QuaZip::mdUnzip))
    {
        qWarning() << "Could not open zip file" << zipFilePath;
        return;
    }
    QDir().mkpath(extractDirPath);
    QuaZipFile zipFile(&zip);

    for(bool more =zip.goToFirstFile(); more; more=zip.goToNextFile())
    {
        if(!zipFile.open(QIODevice::ReadOnly))
        {
            qWarning() << "Could not open zip file for reading";
            continue;
        }

        QFile outFile(extractDirPath + "/" + zipFile.getActualFileName());
        if(!outFile.open(QIODevice::WriteOnly))
        {
            qWarning()<< "Could not create output file" <<outFile.fileName();
            zipFile.close();
            continue;
        }

        outFile.write(zipFile.readAll());
        outFile.close();
        zipFile.close();
    }

    zip.close();
}
