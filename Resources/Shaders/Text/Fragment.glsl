#version 400

layout (location = 0) out vec4 out_color;

in VertexData
{
	vec2 uv;
} i;

uniform sampler2D sampler;
uniform vec3 color;

void main(void)
{
	vec4 sampled_value = vec4(1.0, 1.0, 1.0, texture(sampler, i.uv).r);
	out_color = vec4(color, 1.0f) * sampled_value;
}