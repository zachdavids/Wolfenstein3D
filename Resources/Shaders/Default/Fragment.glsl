#version 400

layout (location = 0) out vec4 out_color;

in VertexData
{
	vec2 uv;
} i;

uniform sampler2D sampler;

void main(void)
{
	vec4 sampled_color = texture(sampler, i.uv);
	
	if (sampled_color.a < 0.1)
	{
		discard;
	}
	
	out_color = sampled_color; 
}