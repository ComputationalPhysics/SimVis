#include "simulator.h"

Simulator::Simulator(QObject *parent) : QObject(parent)
{
    connect(&m_timer, &QTimer::timeout, this, &Simulator::step);
    m_timer.start(1);
}

Simulator::~Simulator()
{
    m_workerThread.quit();
    m_workerThread.wait();
}

void Simulator::step()
{
    if(!m_worker) {
        m_worker = createWorker();
        m_worker->moveToThread(&m_workerThread);
        m_workerThread.start();
    }
    if(m_workerMutex.tryLock()) {
        m_worker->synchronizeSimulator(this);
        emit requestVisualizerSync(m_worker);
        QMetaObject::invokeMethod(m_worker, "workAndUnlock", Qt::QueuedConnection, Q_ARG(Simulator*, this));
    }
}

void SimulatorWorker::workAndUnlock(Simulator* simulator)
{
    work();
    simulator->m_workerMutex.unlock();
}
