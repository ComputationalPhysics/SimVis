import QtQuick 2.0

Item {
    property Value position: Value {
        type: "vec3"
        header: "in vec3 position;\n"
        initialization: ""
        result: "position"
        identifier: "position"
    }
    property Value normal: Value {
        type: "vec3"
        header: "in vec3 normal;\n"
        initialization: ""
        result: "normal"
        identifier: "normal"
    }
}
