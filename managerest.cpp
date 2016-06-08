#include "managerest.h"

#include <iostream>

ManageRest::ManageRest(QObject *parent) : QObject(parent)
{
}


void ManageRest::doUpload(const std::vector<QString>& jsons)
{
    QNetworkRequest req(QUrl("http://httpbin.org/"));
    m_manager = new QNetworkAccessManager(this);

    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyManage(QNetworkReply*)));

    for(const auto& it : jsons )
    {
        QByteArray b = it.toUtf8();
        std::cout << b.toStdString() << std::endl;
        m_manager->post(req, b);
    }
}


void ManageRest::replyManage (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        disconnect (m_manager, SIGNAL (finished(QNetworkReply *)), this, SLOT (replyManage (QNetworkReply  *)));
    }
}
