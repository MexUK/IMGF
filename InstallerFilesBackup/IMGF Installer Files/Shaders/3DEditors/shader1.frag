#version 330

in vec2 texcoord;
in vec3 colour;
uniform sampler2D tex;
out vec4 out_colour;

void main(void)
{
	vec3 tex = texture(tex, texcoord).xyz;
	vec3 vert = colour;
	vec3 col = tex * vert;
	out_colour = vec4(col, 1.0);
}

