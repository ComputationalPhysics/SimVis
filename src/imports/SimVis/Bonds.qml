import SimVis 1.0
import SimVis.ShaderNodes 1.0
import SimVis.ShaderNodes 1.0 as Nodes

import Qt3D.Core 2.0
import Qt3D.Render 2.0

import QtQuick 2.0 as QQ2

Entity {
    id: bondsRoot
    property var variable: 0.0
    property alias fragmentColor: _fragmentColor.value
    property alias fragmentBuilder: _fragmentBuilder
    property alias normal: _fragmentBuilder.normal
    property alias position: _fragmentBuilder.position
    property alias transform: transform

    property BondData bondData

    Transform {
        id: transform
    }

    Material {
        id: material
        effect: Effect {
            techniques: Technique {
                renderPasses: RenderPass {
                    bindings: [
                        ParameterMapping {
                            parameterName: "vertex1Position"
                            shaderVariableName: "vertex1Position"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "vertex2Position"
                            shaderVariableName: "vertex2Position"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "radius1"
                            shaderVariableName: "radius1"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "radius2"
                            shaderVariableName: "radius2"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "sphereRadius1"
                            shaderVariableName: "sphereRadius1"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "sphereRadius2"
                            shaderVariableName: "sphereRadius2"
                            bindingType: ParameterMapping.Attribute
                        },
                        ParameterMapping {
                            parameterName: "vertexId"
                            shaderVariableName: "vertexId"
                            bindingType: ParameterMapping.Attribute
                        }
                    ]
                    shaderProgram: ShaderProgram {
                        vertexShaderCode: loadSource("qrc:/SimVis/render/shaders/gl3/bonds.vert")
                        fragmentShaderCode: _fragmentBuilder.finalShader
                    }
                    ShaderBuilder {
                        id: _fragmentBuilder

                        material: material

                        // TODO add readonly or some other way to show that these are only for others to read
                        shaderType: ShaderBuilder.Fragment

                        // inputs
                        property ShaderNode position: ShaderNode {
                            type: "vec3"
                            name: "position"
                            result: "position"
                        }
                        property ShaderNode normal: ShaderNode {
                            type: "vec3"
                            name: "normal"
                            result: "normal"
                        }
                        property ShaderNode textureCoordinate: ShaderNode {
                            type: "vec2"
                            name: "texCoord"
                            result: "texCoord"
                        }

                        sourceFile: "qrc:/SimVis/render/shaders/gl3/bonds.frag"

                        outputs: [
                            ShaderOutput {
                                id: _fragmentColor
                                type: "vec4"
                                name: "fragColor"
                                value: StandardMaterial { }
                            }
                        ]
                    }
                }
            }
        }
    }
    GeometryRenderer {
        id: bondsMeshInstanced
        primitiveType: GeometryRenderer.TriangleStrip
        enabled: instanceCount != 0
        instanceCount: bondData ? bondData.count : 0

        geometry: PointGeometry {
            attributes: [
                Attribute {
                    name: "vertex1Position"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 3
                    byteOffset: 0
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData ? bondData.buffer : null
                },
                Attribute {
                    name: "vertex2Position"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 3
                    byteOffset: 3 * 4
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData ? bondData.buffer : null
                },
                Attribute {
                    name: "sphereRadius1"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 1
                    byteOffset: 6 * 4
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData ? bondData.buffer : null
                },
                Attribute {
                    name: "sphereRadius2"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 1
                    byteOffset: 7 * 4
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData.buffer
                },
                Attribute {
                    name: "radius1"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 1
                    byteOffset: 8 * 4
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData.buffer
                },
                Attribute {
                    name: "radius2"
                    attributeType: Attribute.VertexAttribute
                    dataType: Attribute.Float
                    dataSize: 1
                    byteOffset: 9 * 4
                    byteStride: (3 + 3 + 1 + 1 + 1 + 1) * 4
                    divisor: 1
                    buffer: bondData ? bondData.buffer : null
                }
            ]
        }

    }

    components: [
        bondsMeshInstanced,
        material,
        transform
    ]
}
