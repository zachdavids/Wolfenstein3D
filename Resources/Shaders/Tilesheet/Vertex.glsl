#version 400

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;

out VertexData
{
	vec2 uv;
} o;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
	gl_Position = projection * view * model * vec4(in_position, 1.0f);
	o.uv = in_uv;
}