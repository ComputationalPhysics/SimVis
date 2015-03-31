uniform sampler2D texture;
varying highp vec2 coords;
varying highp vec3 color;
varying highp float attenuationFactor;
varying highp vec3 vertexPosition;
varying highp float sphereId;

void main() {
    highp vec3 light = vec3(1.0, 1.0, 1.0);
    highp float x = 2.0*coords.s - 1.0;
    highp float y = 2.0*coords.t - 1.0;
    highp float r2 = x*x + y*y;
    highp float z = sqrt(1.0 - r2); // Equation for sphere, x^2 + y^2 + z^2 = R^2

    highp vec3 normal = x*cp_rightVector - y*cp_upVector - z*cp_viewVector;

#ifdef DEFAULTLIGHT

#ifdef SIMPLEXBUMP
    normal = simplexbump(normal, normal+vec3(sphereId));
#endif

    light = defaultLight(normal, vertexPosition, color);
#endif

    if(r2 > 0.9) {
        // 0.9 so we don't get this light circle on the back of the spheres
        discard;
    }

    gl_FragColor = vec4(color*light, 1.0);
}
