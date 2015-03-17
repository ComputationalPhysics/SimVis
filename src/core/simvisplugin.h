#ifndef SIMVISPLUGIN_H
#define SIMVISPLUGIN_H

#include <QQmlExtensionPlugin>

class SimVisPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    SimVisPlugin();

    void registerTypes(const char *uri);

    // QQmlExtensionInterface interface
public:
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // SIMVISPLUGIN_H
