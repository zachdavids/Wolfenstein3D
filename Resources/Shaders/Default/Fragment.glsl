#version 400

layout (location = 0) out vec4 out_color;

in VertexData
{
	vec2 uv;
} i;

uniform sampler2D sampler;

void main(void)
{
	out_color = texture(sampler, i.uv);
}