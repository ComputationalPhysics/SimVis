in vec2 texCoord;
in vec3 vertexPosition;
in float da;
out vec4 fragcolor;

void main(void) {
    vec3 color = vec3(0.0, 1.0, 1.0);
    highp float x = texCoord.s;
    highp float y = texCoord.t;
    highp float r = sqrt(x*x + y*y);
    if(r > 1.0) {
        discard;
    }
//    float yy = y*y;
//    if(yy > 1.0) {
//        discard;
//    }
//    fragcolor = vec4(1.0, 0.5, 0.5, 1.0);

////    float dada = da*da;
////    if(x<0.0) {
////        if(x*x + yy*dada > dada) { discard; }
////    }

//    highp vec3 light = vec3(1.0, 1.0, 1.0);
//    highp float z = sqrt(1.0 - yy);

    fragcolor = vec4(r, 0.5, 0.5, 1.0);
//        fragcolor = vec4(1.0, 0.5, 0.5, 1.0);
}
