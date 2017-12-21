#version 150

// Simple example with transformation matrices

in  vec3 in_Position;
in  vec3 in_Color;
uniform mat4 Projection;
uniform mat4 Model;
uniform mat4 Camera;
out vec3 outColour;

void main(void)
{
	outColour = in_Color;
	gl_Position = Model * Camera * vec4(in_Position, 1.0);
}
