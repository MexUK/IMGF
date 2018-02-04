#version 330

in vec3 in_position;
in vec2 in_texcoord;
in vec3 in_colour;
in vec3 in_normal;
in int in_iHasTexture;
uniform mat4 model;
uniform mat4 camera;
out vec2 texcoord;
out vec3 colour;
flat out int iHasTexture;

void main(void)
{
	gl_Position = camera * model * vec4(in_position, 1.0);
	
	texcoord = in_texcoord;
	colour = in_colour;
	//iHasTexture = in_iHasTexture;
}

