#include <QCoreApplication>
#include <iostream>
#include <QtCore>
#include <QFile>
#include "filedownload.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FileDownload d;
    d.doDownload();
    return a.exec();
}
