#include "mysimulator.h"
#include "lammps/library.h"
#include "lammps/atom.h"
#include "lammps/domain.h"
#include "lammps/update.h"
#include <string>
#include <sstream>
#include <SimVis/Spheres>
#include <QUrl>
#include <QString>
#include <QQmlFile>

using std::string;

MySimulator::MySimulator()
{

}

MySimulator::~MySimulator()
{

}

bool MySimulator::discoMode() const
{
    return m_discoMode;
}

int MySimulator::simulationSpeed() const
{
    return m_simulationSpeed;
}

void MySimulator::setDiscoMode(bool arg)
{
    if (m_discoMode == arg)
        return;

    m_discoMode = arg;
    emit discoModeChanged(arg);
}

void MySimulator::loadSimulation(QString simulation)
{

}

void MySimulator::setSimulationSpeed(int arg)
{
    if (m_simulationSpeed == arg)
        return;

    m_simulationSpeed = arg;
    emit simulationSpeedChanged(arg);
}

void MyWorker::loadSimulation(QString inputScript) {
    if(lammps) {
        lammps_close((void*)lammps);
        lammps = 0;
    }

    lammps_open_no_mpi(0, 0, (void**)&lammps);
    QFile file(inputScript);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open file: " << file.fileName();
    }
    QString content = file.readAll();
    runCommands(content.toStdString().c_str());
}

MyWorker::MyWorker() {
    loadSimulation(":/in.lennardjonesdiffusion");
}

void MyWorker::runCommands(const char *commands) {
    std::stringstream ss(commands);
    std::string to;

    if (commands != NULL)
    {
        while(std::getline(ss,to,'\n')){
            runCommand(to.c_str());
        }
    }
}

void MyWorker::runCommand(const char *command)
{
    if(lammps == 0) {
        qDebug() << "Warning, trying to run a LAMMPS command with no LAMMPS object. You need to load a simulation first.";
        qDebug() << "Command: " << command;
        return;
    }

    lammps_command((void*)lammps, (char*) command);
}

void MyWorker::synchronizeSimulator(Simulator *simulator)
{
    MySimulator *mySimulator = qobject_cast<MySimulator*>(simulator);
    m_discoMode = mySimulator->discoMode();
    m_simulationSpeed = mySimulator->simulationSpeed();
}

void MyWorker::synchronizeRenderer(Renderable *renderableObject)
{
    Spheres* spheres = qobject_cast<Spheres*>(renderableObject);
    if(spheres) {
        QVector<QVector3D> &positions = spheres->positions();
        QVector<QColor> &colors = spheres->colors();
        colors.resize(lammps->atom->natoms);
        positions.resize(lammps->atom->natoms);
        double position[3];
        QColor color1(255.0, 0.0, 0.0);
        QColor color2(0.0, 255.0, 0.0);

        for(unsigned int i=0; i<lammps->atom->natoms; i++) {
            position[0] = lammps->atom->x[i][0];
            position[1] = lammps->atom->x[i][1];
            position[2] = lammps->atom->x[i][2];
            lammps->domain->remap(position);

            positions[i][0] = position[0] - lammps->domain->prd_half[0];
            positions[i][1] = position[1] - lammps->domain->prd_half[0];
            positions[i][2] = position[2] - lammps->domain->prd_half[0];
            if(m_discoMode) {
                colors[i].setRedF(std::min(1.0, fabs(lammps->atom->v[i][0])));
                colors[i].setGreenF(std::min(1.0, fabs(lammps->atom->v[i][1])));
                colors[i].setBlueF(std::min(1.0, fabs(lammps->atom->v[i][2])));
            } else {
                colors[i] = (lammps->atom->type[i] == 1) ? color1 : color2;
            }
        }

        return;
    }
}

void MyWorker::work()
{
    //    if( (m_timestepsSinceLastPreRun % 100) == 0) {
    //        for(QString &command : m_queuedCommands) {
    //            lammps_command((void*)lammps, (char*)command.toStdString().c_str());
    //        }

    //        m_lastPreRun = lammps->update->ntimestep;
    //        QString cmd = QString("run 1 start %1 stop %2").arg(m_lastPreRun).arg(m_lastPreRun+100);

    //        runCommand(cmd.toStdString().c_str());
    //    } else {
    //        QString cmd = QString("run 1 pre no post no start %1 stop %2").arg(m_lastPreRun).arg(m_lastPreRun+100);
    //        runCommand(cmd.toStdString().c_str());
    //    }
    runCommand(QString("run %1 pre no post no").arg(m_simulationSpeed).toStdString().c_str());
}

MyWorker *MySimulator::createWorker()
{
    return new MyWorker();
}
