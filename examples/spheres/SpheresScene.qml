import Qt3D.Core 2.0
import Qt3D.Render 2.0

import QtQuick 2.0 as QQ2
import QtQuick.Scene3D 2.0

import MySimulator 1.0

Scene3D {
    anchors.fill: parent
    anchors.margins: 10
    focus: true
    aspects: "input"

    Entity {
        Camera {
            id: camera
            projectionType: CameraLens.PerspectiveProjection
            fieldOfView: 22.5
            aspectRatio: 16/9
            nearPlane : 0.1
            farPlane : 1000.0
            position: Qt.vector3d(10.0, 7.0, 35.0)
            upVector: Qt.vector3d(0.0, 1.0, 0.0)
            viewCenter: Qt.vector3d(10.0, 0.5, 0.0)
        }

        Configuration  {
            controlledCamera: camera
        }

        components: [
            FrameGraph {
                activeFrameGraph: TechniqueFilter {
                    requires: [
                        Annotation {
                            name: "renderingStyle"
                            value: "forward"
                        }
                    ]
                    Viewport {
                        id: viewport
                        rect: Qt.rect(0.0, 0.0, 1.0, 1.0)
                        clearColor: "steelblue"
                        CameraSelector {
                            id : cameraSelector
                            camera: camera
                            FrustumCulling {
                                enabled: false
                                ClearBuffer {
                                    buffers : ClearBuffer.ColorDepthBuffer
                                }
                            }
                        }
                    }
                }
            }
        ]
        SpheresEntity {
            simulator: MySimulator {
                dt: 0.1
            }
        }
    }
}
