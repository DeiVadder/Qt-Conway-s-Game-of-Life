#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "gameboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    GameBoard game;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("Gameboard", &game);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
