#version 400

layout (location = 0) out vec4 out_color;

in VertexData
{
	vec2 uv;
} i;

uniform sampler2D sampler;

void main(void)
{
	vec4 sampled_value = texture(sampler, i.uv);
	out_color = sampled_value;
}