#version 330

in vec2 texcoord;
in vec3 colour;
//flat in int iHasTexture;
uniform sampler2D tex;
out vec4 out_colour;

void main(void)
{
	//int ttt = iHasTexture;
	
	//if(ttt == 1)
	//	out_colour = vec4(texture(tex, texcoord).xyz, 1.0);
	//else
	//	out_colour = vec4(colour, 1.0);
	
	vec3 tex = texture(tex, texcoord).xyz;
	vec3 vert = colour;
	vec3 col = tex * vert;
	out_colour = vec4(col, 1.0);
}

