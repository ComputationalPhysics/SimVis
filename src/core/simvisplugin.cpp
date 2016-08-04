#include "simvisplugin.h"
#include "simulator.h"
#include "../renderables/billboards/billboards.h"
#include "../renderables/points/points.h"
#include "../renderables/spheres/spheres.h"
#include "../renderables/cylinders/cylinders.h"
#include "../renderables/bonds/bonds.h"
#include "../renderables/lines/lines.h"
#include "../renderables/marchingcubes/marchingcubes.h"
#include "../renderables/skybox/skybox.h"
#include "visualizer.h"
#include "camera.h"
#include "navigator.h"
#include "navigators/trackballnavigator.h"
#include "navigators/flymodenavigator.h"
#include "../shadereffects/simplexbump.h"
#include "../shadereffects/light.h"
#include "../shadereffects/simplextexture.h"
#include "../shadereffects/skyboxreflection.h"
#include "../renderables/trianglecollection/trianglecollection.h"
#include "../renderables/noiseviewer/noiseviewer.h"
#include "../shadereffects/periodiccopies.h"
#include "../shadereffects/customcolor.h"
#include "../shadereffects/slice.h"
#include <qqml.h>
#include <QQmlEngine>

void SimVisPlugin::registerTypes(const char *uri)
{
    Q_INIT_RESOURCE(simvis_shaders);
    Q_INIT_RESOURCE(simvis_qmldir);
    // @uri SimVis
    Q_ASSERT(uri == QLatin1String("SimVis"));
    qmlRegisterUncreatableType<Simulator>("SimVis", 1, 0, "Simulator",
                                          "Cannot create abstract type Simulator. This must be subclassed.");
    qmlRegisterType<Billboards>("SimVis", 1, 0, "Billboards");
    qmlRegisterType<Spheres>("SimVis", 1, 0, "Spheres");
    qmlRegisterType<MarchingCubes>("SimVis", 1, 0, "MarchingCubes");
    qmlRegisterType<Points>("SimVis", 1, 0, "Points");
    qmlRegisterType<Visualizer>("SimVis", 1, 0, "Visualizer");
    qmlRegisterType<Camera>("SimVis", 1, 0, "Camera");
    qmlRegisterType<Navigator>("SimVis", 1, 0, "Navigator");
    qmlRegisterType<TrackballNavigator>("SimVis", 1, 0, "TrackballNavigator");
    qmlRegisterType<FlyModeNavigator>("SimVis", 1, 0, "FlyModeNavigator");
    qmlRegisterType<SimplexBump>("SimVis", 1, 0, "SimplexBump");
    qmlRegisterType<SimplexTexture>("SimVis", 1, 0, "SimplexTexture");
    qmlRegisterType<Light>("SimVis", 1, 0, "Light");
    qmlRegisterType<SkyBox>("SimVis", 1, 0, "SkyBox");
    qmlRegisterType<SkyBoxReflection>("SimVis", 1, 0, "SkyBoxReflection");
    qmlRegisterType<TriangleCollection>("SimVis", 1, 0, "TriangleCollection");
    qmlRegisterType<NoiseViewer>("SimVis", 1, 0, "NoiseViewer");
    qmlRegisterType<PeriodicCopies>("SimVis", 1, 0, "PeriodicCopies");
    qmlRegisterType<Slice>("SimVis", 1, 0, "Slice");
    qmlRegisterType<Cylinders>("SimVis", 1, 0, "Cylinders");
    qmlRegisterType<Bonds>("SimVis", 1, 0, "Bonds");
    qmlRegisterType<Lines>("SimVis", 1, 0, "Lines");
    qmlRegisterType<CustomColor>("SimVis", 1, 0, "CustomColor");
}

void SimVisPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(engine);
    Q_UNUSED(uri);
}


