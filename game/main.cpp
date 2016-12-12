#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "ball.h"
#include "physicalengine.h"
#include <pocket.h>
#include <QQuickView>
int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
    qmlRegisterType<Ball>("ball", 1, 0, "Ball");
    qmlRegisterType<physicalEngine>("PhysicalEngine", 1, 0, "PhysicalEngine");
    qmlRegisterType<Pocket>("Pocket", 1, 0, "Pocket");

    //engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QQuickView view;
    view.setSource(QUrl(QLatin1String("qrc:/main.qml")));
    view.setWidth(800);
    view.setHeight(400);

    view.show();

    return app.exec();
}
