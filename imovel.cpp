#include "imovel.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

Imovel::Imovel()
{

}

void Imovel::addImmobile(const immobile_t & immobile){
    m_immobiles.emplace_back(immobile);
}

void Imovel::createJson()
{
    for(auto it = m_immobiles.begin(); it != m_immobiles.end(); ++it)
    {
        QJsonObject json;
        json["propertyCode"] = QString(it->cd.c_str());
        json["propertyType"] = QString(it->type.c_str());
        json["description"] =QString(it->description.c_str());
        json["updatedAt"] = QString(it->updatedAt.c_str());
        QJsonArray jArrayAddress;
        {
            QJsonObject jsonTemp;
            jsonTemp["city"] = QString(it->city.c_str());
            jsonTemp["neighbourhood"] = QString(it->neighbourhood.c_str());
            jsonTemp["number"] = QString(it->number.c_str());
            jsonTemp["complement"] = QString(it->complement.c_str());
            jsonTemp["zipCode"] = QString(it->zipCode.c_str());
            jArrayAddress.append(jsonTemp);
        }
        json["address"] = jArrayAddress;

        QJsonArray jArrayPhotos;
        for(auto&& item: it->photos)
        {
            QJsonObject jsonTemp;
            jsonTemp["url"] = QString(item.c_str());
            jArrayPhotos.append(jsonTemp);
        }
        json["photos"] = jArrayPhotos;

        m_jsonArray.append(json);
    }
}

QJsonArray Imovel::getJsonsImoveis() const
{
    return m_jsonArray;
}
