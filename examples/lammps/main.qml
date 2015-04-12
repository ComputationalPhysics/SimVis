import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.0
import MySimulator 1.0
import SimVis 1.0

ApplicationWindow {
    id: applicationRoot
    title: qsTr("Lammps diffusion demo")
    width: 1650
    height: 900
    visible: true

    MySimulator {
        id: simulator
    }

    Visualizer {
        id: visualizer
        width: applicationRoot.width
        height: applicationRoot.height - row1.height
        simulator: simulator
        camera: camera
        backgroundColor: "#111"
        navigator: navigator

        TrackballNavigator {
            id: navigator
            anchors.fill: parent
            camera: camera
        }

        Spheres {
            id: spheres
            visible: true
            scale: 0.5
            color: "pink"

            Light {
                id: light
                ambientColor: spheres.color
                specularColor: "white"
                diffuseColor: spheres.color
                ambientIntensity: 0.025
                diffuseIntensity: 0.5
                specularIntensity: 1.0
                shininess: 40.0
                attenuation: 0.01
                position: camera.position
            }

            Light {
                id: light2
                ambientColor: spheres.color
                specularColor: "white"
                diffuseColor: spheres.color
                ambientIntensity: 0.025
                diffuseIntensity: 0.5
                specularIntensity: 1.0
                shininess: 40.0
                attenuation: 0.01
                position: Qt.vector3d(Math.sin(0.1*6.28*visualizer.time), Math.cos(0.1*6.28*visualizer.time), 0)
            }
        }
    }

    Camera {
        id: camera
        nearPlane: 0.1
    }

    FastBlur {
        id: blurEffect
        anchors.fill: visualizer
        source: visualizer
    }

    Row {
        id: row1
        anchors.top: visualizer.bottom
        spacing: 10

        Slider {
            id: simulationSpeedSlider
            minimumValue: 1
            maximumValue: 10
            stepSize: 1
            value: 1
            onValueChanged: simulator.simulationSpeed = value
        }
        Label {
            text: qsTr("Simulation speed: %1").arg(simulator.simulationSpeed.toFixed(0))
        }
    }

    Item {
        x: 0.5*(parent.width - width)
        width: buttonDiffusion.width + buttonCrystal.width + buttonWater.width + buttonGashydrates.width
        opacity: 0.9

        Row {
            id: simulationRow1
            anchors.left: parent.left
            anchors.top: parent.top
            Button {
                id: buttonDiffusion
                anchors.leftMargin: 3
                text: "Diffusion"
                onClicked: simulator.loadSimulation("lennardjonesdiffusion")
            }

            Button {
                id: buttonCrystal
                anchors.leftMargin: 3
                text: "Crystal"
                onClicked: simulator.loadSimulation("lennardjonescrystal")
            }

            Button {
                id: buttonWater
                anchors.leftMargin: 3
                text: "Water"
                onClicked: simulator.loadSimulation("bulkwater")
            }
        }

        Row {
            id: simulationRow2
            anchors.left: parent.left
            anchors.top: simulationRow1.bottom

            Button {
                id: buttonGashydrates
                anchors.leftMargin: 3
                text: "Gas hydrates"
                onClicked: simulator.loadSimulation("gashydrates")
            }

            Button {
                id: buttonCrack
                anchors.leftMargin: 3
                text: "Crack"
                onClicked: simulator.loadSimulation("crack")
            }

            Button {
                id: buttonFriction
                anchors.leftMargin: 3
                text: "Friction"
                onClicked: simulator.loadSimulation("friction")
            }
        }

        Row {
            id: simulationRow3
            anchors.left: parent.left
            anchors.top: simulationRow2.bottom

            Button {
                id: buttonFlowPoiseuille
                anchors.leftMargin: 3
                text: "Poiseuille flow"
                onClicked: simulator.loadSimulation("flowpoiseuille")
            }

            Button {
                id: buttonFlowCouette
                anchors.leftMargin: 3
                text: "Couette flow"
                onClicked: simulator.loadSimulation("flowcouette")
            }

            Button {
                id: buttonObstacle
                anchors.leftMargin: 3
                text: "Obstacle"
                onClicked: simulator.loadSimulation("obstacle")
            }
        }




    }

//    LightControl {
//        id: lightControl
//        light: light
//        x: applicationRoot.width*0.5 - width*0.5
//        y: applicationRoot.height*0.5 - height*0.5
//        visible: false
//    }

//    SimulatorControl {
//        id: simulatorControl
//        simulator: simulator
//        x: applicationRoot.width*0.5 - width*0.5
//        y: applicationRoot.height*0.5 - height*0.5
//        visible: false
//    }

//    RenderControl {
//        id: renderControl
//        simplexBump: simplexBump
//        spheres: spheres
//        x: applicationRoot.width*0.5 - width*0.5
//        y: applicationRoot.height*0.5 - height*0.5
//        visible: false
//    }
}
