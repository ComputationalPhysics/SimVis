layout(location=0) in vec3 position;
layout(location=1) in vec3 colorIn;
layout(location=2) in float scaleIn;
layout(location=3) in float sphereIdIn;
out vec3 vs_color;
out vec3 vs_vertexPosition;
out float vs_scale;
out float vs_sphereId;

void main(void)
{
    gl_Position = cp_modelViewProjectionMatrix * vec4(position, 1.0);
    vs_vertexPosition = position;
    vs_color = colorIn;
    vs_scale = scaleIn;
    vs_sphereId = sphereIdIn;
}
