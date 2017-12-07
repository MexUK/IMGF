#version 150

// Simple example with transformation matrices

in  vec3 in_Position;
in  vec3 inNormal;
in  vec2 in_Texcoord;
uniform mat4 Projection;
uniform mat4 ModelView;
out vec3 exNormal; // Phong
out vec2 texcoord;

void main(void)
{
	exNormal = inNormal; // Phong
	
	texcoord = in_Texcoord;
	
	gl_Position = Projection * ModelView * vec4(in_Position, 1.0);
}
