#pragma once
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QMutex>

class Renderable;
class Simulator;

class SimulatorWorker : public QObject {
    Q_OBJECT
public:
    virtual void synchronizeSimulator(Simulator *simulator) = 0;
    virtual void synchronizeRenderer(Renderable *renderableObject) = 0;
    virtual void work() = 0;

    Q_INVOKABLE void workAndUnlock(Simulator *simulator);
signals:
    void workDone();
};

class Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Simulator(QObject *parent = 0);
    ~Simulator();
protected:
    virtual SimulatorWorker *createWorker() = 0;

signals:
    void requestVisualizerSync(SimulatorWorker *worker);

public slots:
    void step();

private:
    SimulatorWorker *m_worker = 0;
    QThread m_workerThread;
    QTimer  m_timer;
    QMutex m_workerMutex;

    friend class Visualizer;
    friend class SimulatorWorker;
};

#endif // SIMULATOR_H
