#include "filedownload.h"

#include <iostream>
#include <QXmlStreamReader>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

#include "jsonserializable.h"
#include "managerest.h"

FileDownload::FileDownload(QObject *parent) : QObject(parent) ,
    m_immobile(new Imovel())
{

}

void FileDownload::doDownload()
{
    m_manager = new QNetworkAccessManager(this);

    m_manager->get(QNetworkRequest(QUrl("http://ahul.github.io/imoveis.xml")));

    connect(m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}

void FileDownload::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << "fetching data";
        QByteArray data(reply->readAll());
        QXmlStreamReader Rxml(data);

        while (!Rxml.atEnd() && !Rxml.hasError())
        {
            QXmlStreamReader::TokenType token = Rxml.readNext();
            if (token == QXmlStreamReader::StartDocument)
            {
                continue;
            }
            if (token == QXmlStreamReader::StartElement)
            {
                if (Rxml.name() == "Imoveis")
                {
                    continue;
                }else if(Rxml.name() == "Imovel")
                {
                    Imovel::immobile_t imTemp;
                    while(!Rxml.atEnd() && !Rxml.hasError())
                    {
                        if(Rxml.isStartElement())
                        {
                          if(Rxml.name() == "CodigoImovel")
                            {
                                imTemp.cd = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "TipoImovel")
                            {
                                imTemp.type = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "Observacao")
                          {
                              std::string temp = Rxml.readElementText().toStdString();
                              std::size_t pos = temp.find(".");
                              imTemp.description = temp.substr(pos + 1);
                              imTemp.updatedAt = temp.substr(0, pos);
                          }else if (Rxml.name() == "Bairro")
                            {
                                imTemp.neighbourhood = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "Numero")
                            {
                                imTemp.number = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "Complemento")
                            {
                                imTemp.complement = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "CEP")
                            {
                                imTemp.zipCode = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "Cidade")
                            {
                                imTemp.city = Rxml.readElementText().toStdString();
                            }else if (Rxml.name() == "URLArquivo")
                            {
                              imTemp.photos.emplace_back(Rxml.readElementText().toStdString());
                            }
                            Rxml.readNext();
                        }else if(Rxml.isEndElement()){
                            if(Rxml.name() == "Fotos"){
                                   m_immobile->addImmobile(imTemp);
                                   imTemp.photos.clear();
                            }
                                Rxml.readNext();
                        }else{
                            Rxml.readNext();
                        }
                    }
                }
            }
        }
    }

    m_immobile->createJson();

    serialize();

    reply->deleteLater();
}

void FileDownload::serialize()
{
    m_listJson = JSonSerializable::serialize(m_immobile->getJsonsImoveis());
    ManageRest rest;
    rest.doUpload(m_listJson);
}

void FileDownload::parser()
{
   QJsonArray jArray;
   JSonSerializable::parse(m_listJson, jArray);
}
