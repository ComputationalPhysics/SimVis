message(Library Deployment)
message(pwd: $$PWD)
message(shadowed_pwd: $$shadowed($$PWD))
message(out_pwd: $$OUT_PWD)

QT += widgets opengl openglextensions qml quick 3dcore 3drender 3dinput 3dquick

INCLUDEPATH += $$PWD/src
QML_IMPORT_PATH += $$PWD/src/imports/

RESOURCES += \
    $$PWD/src/simvis_shaders.qrc \
    $$PWD/src/imports/simvis_imports.qrc

SOURCES += \
    $$PWD/src/core/camera.cpp \
    $$PWD/src/core/navigator.cpp \
    $$PWD/src/core/quickworker.cpp \
    $$PWD/src/core/renderable.cpp \
    $$PWD/src/core/simulator.cpp \
    $$PWD/src/core/simvisplugin.cpp \
    $$PWD/src/navigators/trackballnavigator.cpp \
    $$PWD/src/core/visualizer.cpp \
    $$PWD/src/core/cameralens.cpp \
    $$PWD/src/core/lookattransform.cpp \
    $$PWD/src/renderables/billboards/billboards.cpp \
    $$PWD/src/renderables/points/points.cpp \
    $$PWD/src/core/shadereffect.cpp \
    $$PWD/src/shadereffects/simplexbump.cpp \
    $$PWD/src/shadereffects/simplextexture.cpp \
    $$PWD/src/renderables/spheres/spheres.cpp \
    $$PWD/src/shadereffects/light.cpp \
    $$PWD/src/renderables/skybox/skybox.cpp \
    $$PWD/src/shadereffects/skyboxreflection.cpp \
    $$PWD/src/renderables/trianglecollection/trianglecollection.cpp \
    $$PWD/src/shadereffects/periodiccopies.cpp \
    $$PWD/src/shadereffects/slice.cpp \
    $$PWD/src/renderables/cylinders/cylinders.cpp \
    $$PWD/src/renderables/lines/lines.cpp \
    $$PWD/src/renderables/noiseviewer/noiseviewer.cpp \
    $$PWD/src/navigators/flymodenavigator.cpp \
    $$PWD/src/shadernodes/shadernode.cpp \
    $$PWD/src/shadernodes/shaderbuilder.cpp \
    $$PWD/src/shadernodes/shaderoutput.cpp \
    $$PWD/src/shadernodes/shadergroup.cpp \
    $$PWD/src/generators/marchingcubes/marchingcubes.cpp \
    $$PWD/src/generators/marchingcubes/marchingcubesgenerator.cpp \
    $$PWD/src/renderables/marchingcubes/marchingcubesgs.cpp \
    $$PWD/src/shadernodes/shaderbuilderbinding.cpp \
    $$PWD/src/shadernodes/shaderutils.cpp \

HEADERS += \
    $$PWD/src/core/navigator.h \
    $$PWD/src/core/quickworker.h \
    $$PWD/src/core/renderable.h \
    $$PWD/src/core/simulator.h \
    $$PWD/src/core/camera.h \
    $$PWD/src/core/simvisplugin.h \
    $$PWD/src/navigators/trackballnavigator.h \
    $$PWD/src/core/visualizer.h \
    $$PWD/src/core/camera_p.h \
    $$PWD/src/core/cameralens.h \
    $$PWD/src/core/cameralens_p.h \
    $$PWD/src/core/lookattransform.h \
    $$PWD/src/core/lookattransform_p.h \
    $$PWD/src/renderables/billboards/billboards.h \
    $$PWD/src/renderables/points/points.h \
    $$PWD/src/SimVis/Billboards \
    $$PWD/src/SimVis/Points \
    $$PWD/src/SimVis/MarchingCubes \
    $$PWD/src/core/shadereffect.h \
    $$PWD/src/shadereffects/simplexbump.h \
    $$PWD/src/shadereffects/simplextexture.h \
    $$PWD/src/renderables/spheres/spheres.h \
    $$PWD/src/SimVis/Spheres \
    $$PWD/src/shadereffects/light.h \
    $$PWD/src/renderables/skybox/skybox.h \
    $$PWD/src/shadereffects/skyboxreflection.h \
    $$PWD/src/renderables/trianglecollection/trianglecollection.h \
    $$PWD/src/SimVis/QuickWorker \
    $$PWD/src/SimVis/Renderable \
    $$PWD/src/SimVis/Simulator \
    $$PWD/src/SimVis/TriangleCollection \
    $$PWD/src/shadereffects/periodiccopies.h \
    $$PWD/src/shadereffects/slice.h \
    $$PWD/src/renderables/cylinders/cylinders.h \
    $$PWD/src/SimVis/Cylinders \
    $$PWD/src/renderables/lines/lines.h \
    $$PWD/src/SimVis/Lines \
    $$PWD/src/renderables/noiseviewer/noiseviewer.h \
    $$PWD/src/SimVis/NoiseViewer \
    $$PWD/src/navigators/flymodenavigator.h \
    $$PWD/src/shadernodes/shadernode.h \
    $$PWD/src/shadernodes/shaderbuilder.h \
    $$PWD/src/shadernodes/shaderoutput.h \
    $$PWD/src/shadernodes/shadergroup.h \
    $$PWD/src/generators/marchingcubes/marchingcubes.h \
    $$PWD/src/generators/marchingcubes/marchingcubesgenerator.h \
    $$PWD/src/renderables/marchingcubes/marchingcubesgs.h \
    $$PWD/src/shadernodes/shaderutils.h \
    $$PWD/src/shadernodes/shaderbuilderbinding.h \
