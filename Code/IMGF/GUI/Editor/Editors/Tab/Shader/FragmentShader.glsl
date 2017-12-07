#version 150

// Color from vertex shader

in vec2 texcoord;
in vec3 outColour;
out vec4 outColor;
uniform sampler2D tex;

void main(void)
{
	outColor = texture(tex, texcoord);
	//outColor = vec4(outColour, 1.0);
}
