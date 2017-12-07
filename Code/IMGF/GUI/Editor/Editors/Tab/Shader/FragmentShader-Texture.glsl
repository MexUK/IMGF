#version 150

// Color from vertex shader

in vec2 texcoord;
uniform sampler2D tex;
out vec4 outColor;

void main(void)
{
	outColor = texture(tex, texcoord);
}
