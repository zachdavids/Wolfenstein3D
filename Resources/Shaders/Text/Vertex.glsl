#version 400

layout (location = 0) in vec4 in_position;

out VertexData
{
	vec2 uv;
} o;

uniform mat4 projection;

void main(void)
{
	gl_Position = projection * vec4(in_position.xy, 0.0, 1.0f);
	o.uv = in_position.zw;
}