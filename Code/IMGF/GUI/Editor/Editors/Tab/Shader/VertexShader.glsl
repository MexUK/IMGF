#version 150

// Simple example with transformation matrices

in  vec3 in_Position;
in  vec2 in_Texcoord;
uniform mat4 Projection;
uniform mat4 ModelView;
out  vec2 texcoord;

void main(void)
{
	gl_Position = Projection * ModelView * vec4(in_Position, 1.0);
	texcoord = in_Texcoord;
}
