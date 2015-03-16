#include "simplesimulator.h"

#include <QVector3D>
#include <QVector2D>

SimulatorWorker *SimpleSimulator::createWorker()
{
    return new SimpleWorker();
}

SimpleWorker::SimpleWorker()
{
    int ballCount = 100;
    m_positions.resize(ballCount);
    m_velocities.resize(ballCount);
    for(auto i=0; i < ballCount; i++) {
        float x =  2.0*(rand() / double(RAND_MAX)) - 1.0;
        float y =  2.0*(rand() / double(RAND_MAX)) - 1.0;
        float vx = 2.0*(rand() / double(RAND_MAX)) - 1.0;
        float vy = 2.0*(rand() / double(RAND_MAX)) - 1.0;

        x *= 0.5;
        y *= 0.5;
        vx *= 0.3;
        vy *= 0.3;

        m_positions[i] = QVector3D(x, y, 0);
        m_velocities[i] = QVector3D(vx, vy, 0);
    }
}

void SimpleWorker::synchronizeSimulator(Simulator *simulator)
{
    SimpleSimulator *sim = static_cast<SimpleSimulator *>(simulator);
    Q_UNUSED(sim)
    // ... synchronize worker and simulator here
}

void SimpleWorker::work()
{
    float m = 1.0;
    float k = 1.0;
    float dt = 0.01;
    for(int i = 0; i < m_positions.size(); i++) {
        QVector3D F;
        QVector3D a;
        QVector3D &r = m_positions[i];
        QVector3D &v = m_velocities[i];

        F = -r*k;
        a = F / m;
        v += a*dt;
        r += v*dt;
    }
}
