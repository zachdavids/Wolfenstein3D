#version 330

layout(location=0) in vec3 in_Position;
layout(location=1) in vec2 in_TextureCoord;

out vec4 frag_Color;
out vec2 texture_Coord;

uniform mat4 transform;

void main(void)
{
	gl_Position = transform * vec4(in_Position, 1.0f);
	frag_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	texture_Coord = in_TextureCoord;
}