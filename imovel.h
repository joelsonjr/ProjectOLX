#ifndef IMOVEL_H
#define IMOVEL_H

#include <QJsonObject>
#include <QJsonArray>

class Imovel
{
public:
    struct immobile_t{
        std::string cd;
        std::string type;
        std::string description;
        std::string updatedAt;
        std::string neighbourhood;
        std::string city;
        std::string number;
        std::string complement;
        std::string zipCode;
        std::vector<std::string> photos;
    };
    Imovel();

    ~Imovel(){}

    void addImmobile(const immobile_t&);
    void createJson();
    QJsonArray getJsonsImoveis() const;
private:
    std::vector<immobile_t> m_immobiles;
    QJsonArray m_jsonArray;
};

#endif // IMOVEL_H
