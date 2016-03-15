import Qt3D.Core 2.0
import Qt3D.Render 2.0

import QtQuick 2.0 as QQ2

import SimVis 1.0 as SimVis
import MySimulator 1.0

Entity {
    id: spheresRoot
    property real variable: 0.0
    property SphereData sphereData
    property Camera camera
    Material {
        id: spheresGeometryShaderTechnique
        parameters: [
            Parameter {
                name: "viewVector"
                value: camera ? camera.viewVector.normalized() : Qt.vector3d(1.0, 0.0, 0.0)
            },
            Parameter {
                name: "upVector"
                value: camera ? camera.upVector.normalized() : Qt.vector3d(0.0, 1.0, 0.0)
            },
            Parameter {
                name: "rightVector"
                value: camera ? camera.viewVector.normalized().crossProduct(camera.upVector.normalized()) : Qt.vector3d(0.0, 0.0, 1.0)
            }
        ]
        effect: Effect {
            techniques: Technique {
                renderPasses: RenderPass {
                    bindings: [
                        ParameterMapping {
                            parameterName: "pos"
                            shaderVariableName: "pos"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "vertexId"
                            shaderVariableName: "vertexId"
                            bindingType: ParameterMapping.Attribute
                        }

                    ]
                    shaderProgram: ShaderProgram {
                        //                        vertexShaderCode: loadSource("qrc:/instanced.vert")
                        //                        geometryShaderCode: loadSource("qrc:/instanced.geom")
                        //                        fragmentShaderCode: loadSource("qrc:/instanced.frag")

                        vertexShaderCode: loadSource("qrc:/spheres.vert")
                        fragmentShaderCode: loadSource("qrc:/spheres.frag")
                    }
                }
            }
        }
    }
    GeometryRenderer {
        id: cylinderMeshInstanced
        primitiveType: GeometryRenderer.TriangleStrip
        enabled: instanceCount != 0
        instanceCount: sphereData.count

        geometry: PointGeometry {
            attributes: [
                instanceDataAttribute
            ]
        }

//        geometry: PlaneGeometry {
//            resolution: Qt.size(2, 2)
//            height: 1.0
//            width: 1.0
//            attributes: [
//                instanceDataAttribute
//            ]
//        }

        Attribute {
            id: instanceDataAttribute
            name: "pos"
            attributeType: Attribute.VertexAttribute
            dataType: Attribute.Float
            dataSize: 3
            divisor: 1
            buffer: sphereData.buffer
        }
    }
//    Transform {
//        id: transform
//        property vector3d cross: camera.viewVector.normalized().crossProduct(Qt.vector3d(0, 1, 0))
//        rotation: fromAxisAndAngle(cross.normalized(), 180/Math.PI*Math.asin(cross.length()))
//        onRotationChanged: {
//            console.log("INFO:")
//            console.log(180/Math.PI*Math.asin(cross.length()))
//            console.log(cross.normalized())
//            console.log(rotation)
//        }

////        rotation: fromAxisAndAngle(cross.normalized(), variable)
//    }
    Entity {
        components: [
            cylinderMeshInstanced,
            spheresGeometryShaderTechnique
        ]
    }
}
