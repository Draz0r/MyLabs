#include "authcontroller.h"
#include <QDebug>
AuthController::AuthController(QObject *parent) : QObject(parent)
{
    na_manager = new QNetworkAccessManager();
}
void AuthController::Authentificate(QString login, QString password)
{
    qDebug() << "Cлот сработал: log = " << login << " pass = " << password;

    emit signalAuthSuccess();

    //QString clientID = "6444409";
QString clientID = "6424413";
    //Строчки далле следуют для синхронного ожидания ответа от сервера
    QEventLoop loop;
    connect(na_manager,SIGNAL(finished(QNetworkReply*)),&loop,SLOT(quit()));

    QNetworkReply * reply = na_manager->get(
                QNetworkRequest(
                    QUrl(
                        "https://oauth.vk.com/authorize"
                        "?client_id=" + clientID +
                        "&display=mobile"
                        "&redirect_uri=https://oauth.vk.com/blank.html"
                        "&scope=friends"
                        "&response_type=token"
                        "&v=5.37"
                        "&state=123456"
                        )
                    )
                );
    //https://oauth.vk.com/authorize?client_id=6444409&display=mobile&redirect_uri=https://oauth.vk.com/blank.html&scope=friends&response_type=token&v=5.37&state=123456
    loop.exec();

    //Должна была прийти форма авторизации
    QString str(reply->readAll());
    qDebug() << "0твет от сервера = " << str;

    //Находим параметры из формы авторизации
    int tag_position = str.indexOf("ip_h");
    tag_position = str.indexOf("value=\"", tag_position);
    QString ip_h = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "ip_h = " << ip_h;

    tag_position = str.indexOf("_origin");
    tag_position = str.indexOf("value=\"", tag_position);
    QString _origin = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "_origin = " << _origin;

    tag_position = str.indexOf("lg_h");
    tag_position = str.indexOf("value=\"", tag_position);
    QString lg_h = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "lg_h = " << lg_h;

    tag_position = str.indexOf("\"to");
    tag_position = str.indexOf("value=\"", tag_position);
    QString to = str.mid(tag_position + 7, str.indexOf('\"',tag_position + 7) - tag_position - 7);
    qDebug() << "to = " << to;


    //Отправим новый запрос с параметрами и логином, паролем. Для дальнейшей работы
    QString authrequest = "https://login.vk.com/"
                          "?act=login"
                          "&soft=1"
                          "&utf8=1"
                          "&_origin=" + _origin +
            "&lg_h=" + lg_h +
            "&ip_h=" + ip_h +
            "&to=" + to +
            "&email=" + login +
            "&pass=" + QUrl::toPercentEncoding(password);

    //QEventLoop l00p;

    QNetworkReply * reply2 = na_manager->get(
                QNetworkRequest(
                    QUrl(authrequest)
                    )
                );

    loop.exec();

    str = reply2->header(QNetworkRequest::LocationHeader).toString();
//    str2(reply2->readAll());
    qDebug() << "Oтвет от сервера2 Header= " << str;


    QNetworkReply * reply3 = na_manager->get(
                QNetworkRequest(
                    QUrl(reply2->header(QNetworkRequest::LocationHeader).toString())
                    )
                );

    loop.exec();
    qDebug() << "*** РЕЗУЛЬТАТ 3 ЗАПРОСА HEADER " << reply3->header(QNetworkRequest::LocationHeader).toString();
    qDebug() << "*** РЕЗУЛЬТАТ 3 ЗАПРОСА BODY " << reply3->readAll();
    QNetworkReply * reply4 = na_manager->get(
    QNetworkRequest(QUrl(
    reply3->header(QNetworkRequest::LocationHeader).toString())));
    loop.exec();
    qDebug() << "*** РЕЗУЛЬТАТ 4 ЗАПРОСА HEADER " << reply4->header(QNetworkRequest::LocationHeader).toString();
    qDebug() << "*** РЕЗУЛЬТАТ 4 ЗАПРОСА BODY " << reply4->readAll();
}

