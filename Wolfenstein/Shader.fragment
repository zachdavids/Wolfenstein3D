#version 330

layout(location=0) out vec4 out_Color;

in vec4 frag_Color;
in vec2 texture_Coord;

uniform vec3 color;
uniform sampler2D sampler;

void main(void)
{
	out_Color = texture(sampler, texture_Coord) * vec4(color, 1.0f);
}