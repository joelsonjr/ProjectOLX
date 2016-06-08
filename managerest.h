#ifndef MANAGEREST_H
#define MANAGEREST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>

class ManageRest : public QObject
{
    Q_OBJECT
public:
    explicit ManageRest(QObject *parent = 0);

    void doUpload(const std::vector<QString>& jsons);

signals:

public slots:
    void replyManage(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_manager;
};

#endif // MANAGEREST_H
