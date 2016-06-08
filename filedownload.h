#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>

#include "imovel.h"

class FileDownload : public QObject
{
    Q_OBJECT

public:
    explicit FileDownload(QObject *parent = 0);

    void doDownload();
    void serialize();
    void parser();

private:
//    void createJson(const std::vector<immobile_t>&);
signals:

public slots:
        void replyFinished (QNetworkReply *reply);

private:
       QNetworkAccessManager *m_manager;
       Imovel *m_immobile;
       std::vector<QString> m_listJson;
};

#endif // FILEDOWNLOAD_H
