#version 430

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform vec3 vCol;

in vec3 vPos;
in vec3 normal;

out vec3 color;
out vec3 position;
out vec3 normalOut;

void main() {
    gl_Position = modelViewProjectionMatrix * vec4(vPos, 1.0);
    color = vCol;
    position = vPos;
    normalOut = normal;
}
