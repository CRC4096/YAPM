#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QtQml>
#include <iostream>

#include "powermeasurementmodel.h"


int main(int argc, char *argv[])
{
    std::cout << "Starting YAPM" << std::endl;

    QGuiApplication::setApplicationName("YAPMApp");
    QGuiApplication::setOrganizationName("QtProject");
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PowerMeasurementModel>("PowerMeasurementModel", 1, 0, "PowerMeasurementModel");
    qmlRegisterSingletonType(QUrl("qrc:/forms/PwrMsrWrapper.qml"), "YAPM.PwrMsrWrapper", 1, 0, "PwrMsrWrapper");

    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/forms/main.qml")));
    return app.exec();
}
