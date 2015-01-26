#include <QGuiApplication>
#include <QtQml>
#include <QQmlApplicationEngine>

#include "gamemodel.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    GameModel game;
    engine.rootContext()->setContextProperty("game", &game);
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
