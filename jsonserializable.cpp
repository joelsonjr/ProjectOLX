#include "jsonserializable.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <iostream>

JSonSerializable::JSonSerializable()
{

}


std::vector<QString> JSonSerializable::serialize(const QJsonArray &objs)
{
    std::vector<QString> results;
   for (const auto& it : objs)
    {
        const QJsonObject& obj = it.toObject();
        QJsonDocument doc(obj);
        QString result(doc.toJson(QJsonDocument::Indented));
        results.emplace_back(result);
    }
    return results;
}

void JSonSerializable::parse(const std::vector<QString>& json, QJsonArray &objs)
{
    for(const auto& it : json)
    {
        const QString& str = it;
        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject jsonObj = document.object();
        objs.append(jsonObj);
    }
}
