#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include <QString>
#include <QJsonArray>

class JSonSerializable
{
public:

//   virtual ~JSonSerializable() {}

    static std::vector<QString> serialize(const QJsonArray &objs);

    static void parse(const std::vector<QString>& json, QJsonArray &objs);

private:
    JSonSerializable();
};

#endif // JSONSERIALIZABLE_H
