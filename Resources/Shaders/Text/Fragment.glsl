#version 400

layout (location = 0) out vec4 out_color;

in VertexData
{
	vec2 uv;
} i;

uniform sampler2D sampler;

void main(void)
{
	vec4 sampled_value = vec4(1.0f, 1.0f, 1.0f, texture(sampler, i.uv).r);
	out_color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * sampled_value;
}