#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "mysimulator.h"
#include "billboards2d.h"
#include "points2d.h"
#include "visualizer.h"
#include "camera.h"
#include "simvisplugin.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<MySimulator>("MySimulator", 1, 0, "MySimulator");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}