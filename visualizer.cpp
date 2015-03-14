#include "visualizer.h"
#include "renderable.h"
#include "billboards2d.h"
#include "simulator.h"

#include <QDebug>
#include <QOpenGLFramebufferObjectFormat>

Visualizer::Visualizer()
{
}

Visualizer::~Visualizer()
{

}

VisualizerRenderer *Visualizer::createRenderer() const
{
    return new VisualizerRenderer();
}

Simulator *Visualizer::simulator() const
{
    return m_simulator;
}

void Visualizer::setSimulator(Simulator *arg)
{
    if (m_simulator == arg) {
        return;
    }
    if(m_simulator) {
        disconnect(m_simulator, &Simulator::requestRendererSync, this, &Visualizer::synchronizeWorker);
    }
    m_simulator = arg;
    connect(m_simulator, &Simulator::requestRendererSync, this, &Visualizer::synchronizeWorker);
    emit simulatorChanged(arg);
}

void Visualizer::synchronizeWorker(SimulatorWorker *worker)
{
    QList<Renderable*> renderables = findChildren<Renderable*>();
    for(Renderable* renderable : renderables) {
        if(worker) {
            worker->synchronizeRenderer(renderable);
        }
    }
    update();
}

void VisualizerRenderer::render()
{
    QOpenGLFunctions funcs(QOpenGLContext::currentContext());
    funcs.glClearColor(0.5f, 0.5f, 0.7f, 1.0f);
    funcs.glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(Renderable* renderable : m_renderables) {
        QMatrix4x4 a;
        renderable->requestRender(a, a);
    }
}

void VisualizerRenderer::synchronize(QQuickFramebufferObject *fbo)
{
    Visualizer* visualizer = static_cast<Visualizer*>(fbo);
    m_renderables = visualizer->findChildren<Renderable*>();
    for(Renderable* renderable : m_renderables) {
        renderable->requestSynchronize();
    }
}

QOpenGLFramebufferObject *VisualizerRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}
