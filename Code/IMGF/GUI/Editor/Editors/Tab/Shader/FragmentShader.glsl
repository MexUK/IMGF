#version 150

// Color from vertex shader

in vec2 texcoord;
out vec4 outColor;
uniform sampler2D tex;

void main(void)
{
	outColor = texture(tex, texcoord);
}
