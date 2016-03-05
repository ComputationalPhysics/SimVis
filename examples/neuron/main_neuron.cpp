#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include "neuronreader.h"

#include <vendor.h>

int main(int argc, char *argv[])
{
    qmlRegisterType<NeuronReader>("NeuroML", 1, 0, "NeuronReader");
//    qmlRegisterType<NeuronRenderable>("NeuroML", 1, 0, "Neuron");

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    qpm::init(app, engine);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}