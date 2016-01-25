// BEGIN spheres.fsh
uniform sampler2D texture;
varying highp vec2 coords;
varying highp vec3 color;
varying highp vec3 vertexPosition;

void main() {
    highp float x = coords.s;
    highp float y = coords.t;
    highp float r2 = x*x + y*y;
    if(r2 > 1.0) {
        // 0.9 so we don't get this light circle on the back of the spheres
        discard;
    } else {
        highp float z = sqrt(1.0 - r2); // Equation for sphere, x^2 + y^2 + z^2 = R^2

        highp vec3 light = vec3(1.0, 1.0, 1.0);
        highp vec3 normal = x*cp_rightVector - y*cp_upVector - z*cp_viewVector;

    #ifdef SIMPLEXBUMP
        normal = simplexbump(normal, normal);
    #endif

    #ifdef DEFAULTLIGHT
        light = defaultLight(normal, vertexPosition, color);
    #endif

    #ifdef SKYBOXREFLECTION
        light += skyboxReflection(normal, vertexPosition);
    #endif

        gl_FragColor = vec4(color*light, 1.0);
    }
}
// END spheres.fsh
