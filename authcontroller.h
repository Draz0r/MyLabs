#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H
#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QEventLoop>

class AuthController : public QObject
{
    Q_OBJECT
public:
    explicit AuthController(QObject *parent = nullptr);
    QNetworkAccessManager * na_manager;
signals:
    signalAuthSuccess();
public slots:
   void Authentificate(QString login, QString password); //параметры такие же
};

#endif // AUTHCONTROLLER_H
