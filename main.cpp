#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "authcontroller.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    AuthController authController; //слот появляется здесь
    QQmlApplicationEngine engine; //чоздается движок-контейнер отрисовки QML
    //ТИП СВЯЗЫВАНИЯ 3: Видимость С++ объекта в QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("authController", //строковое имя для QML
                                &authController); //Перемещаемый объект
    //Именно это функция добовляет в контекст (область витдимости QML)
    engine.load(QUrl(QStringLiteral("qrc:/main.qml"))); //Стартовый QML файл
    if (engine.rootObjects().isEmpty())
        return -1;
    // сигнал пoтенциально может аозникнуть здесь
    //ТИП СВЯЗЫВАНИЯ 1: Видимость QML объекта из С++
    //можно вызывать такой код только после загрузки движка и QML-файла
    QObject * appWindow = engine.rootObjects().first(); //ссылка на QML окно, обладателя сигнала
	// Затем следует -
    //ТИП СВЯЗЫВАНИЯ 2: Связь QML-сигнала с С++-слотом
    //можно вызывать такой код только после загрузки движка,
    //QML-файла и объета обладателя слота
    QObject::connect(appWindow,
                     SIGNAL(sendAuth(QString,QString)),//чей и какой сигнал
                     &authController,
                     SLOT(Authentificate(QString,QString))); 
    return app.exec();
}
