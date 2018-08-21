#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>


int main(int argc, char *argv[])
{
    std::cout << "Starting YAPM" << std::endl;

    QGuiApplication::setApplicationName("Gallery");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/forms/main.qml")));
    return app.exec();
}
