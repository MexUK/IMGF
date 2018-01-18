#version 150

// Simple example with transformation matrices

in vec3 in_Position;
in vec3 in_Color;
uniform mat4 model;
uniform mat4 camera;
out vec3 outColour;

void main(void)
{
	outColour = in_Color;
	gl_Position = model * camera * vec4(in_Position, 1.0);
}
