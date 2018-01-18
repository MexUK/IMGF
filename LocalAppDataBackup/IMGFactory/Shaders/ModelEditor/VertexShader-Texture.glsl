#version 150

// Simple example with transformation matrices

in vec3 in_Position;
in vec3 inNormal;
in vec2 in_Texcoord;
uniform mat4 model;
uniform mat4 camera;
out vec3 exNormal;
out vec2 texcoord;

void main(void)
{
	exNormal = inNormal;
	
	texcoord = in_Texcoord;
	
	gl_Position = model * camera * vec4(in_Position, 1.0);
}
