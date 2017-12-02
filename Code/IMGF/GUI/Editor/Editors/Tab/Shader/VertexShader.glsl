#version 150

uniform mat4 mvp;

in vec2 position;
in vec2 texcoord;

out vec2 Texcoord;


void main() {
    Texcoord = texcoord;
    gl_Position =  mvp * vec4(position, 0.0, 1.0) ;
}