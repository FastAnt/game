#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include "ball.h"
#include "physicalengine.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<Ball>("com.mycompany.ball", 1, 0, "Ball");
    qmlRegisterType<physicalEngine>("com.mycompany.PhysicalEngine", 1, 0, "PhysicalEngine");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    app.setProperty("width",800);
app.setProperty("height",400);
    return app.exec();
}
