import SimVis 1.0
import SimVis.ShaderNodes 1.0
import SimVis.ShaderNodes 1.0 as Nodes

import Qt3D.Core 2.0
import Qt3D.Render 2.0

import QtQuick 2.0 as QQ2
import QtQuick.Scene3D 2.0

import MySimulator 1.0

Scene3D {
    aspects: "input"
    property alias r: fsEntity.r
    property alias nearPlane: fsEntity.nearPlane
    property alias farPlane: fsEntity.farPlane

    Entity {
        Configuration  {
            controlledCamera: frameGraph.camera
        }

        components: [
            StandardFrameGraph {
                id: frameGraph
            }
        ]

        FunctionSurfaceEntity {
            id: fsEntity
            camera: frameGraph.camera
        }
    }
}
