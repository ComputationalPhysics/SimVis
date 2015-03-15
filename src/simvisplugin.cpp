#include "simvisplugin.h"
#include "simulator.h"
#include "billboards2d.h"
#include "points2d.h"
#include "renderable.h"
#include "visualizer.h"

#include <qqml.h>

void SimVisPlugin::registerTypes(const char *uri)
{
    // @uri SimVis
    Q_ASSERT(uri == QLatin1String("SimVis"));
    qmlRegisterInterface<Simulator>("Simulator");
    qmlRegisterType<Billboards2D>("SimVis", 1, 0, "Billboards2D");
    qmlRegisterType<Points2D>("SimVis", 1, 0, "Points2D");
    qmlRegisterType<Visualizer>("SimVis", 1, 0, "Visualizer");
//    qmlRegisterType<Camera>("SimVis", 1, 0, "Camera");
}

