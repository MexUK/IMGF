#version 150

// Color from vertex shader

in vec3 outColour;
out vec4 outColor;

void main(void)
{
	outColor = vec4(outColour, 1.0);
}
