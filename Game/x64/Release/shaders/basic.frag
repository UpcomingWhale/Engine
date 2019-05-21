#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
uniform sampler2D texture1;
in DATA
{
	vec4 position;
	vec4 Ocolor;
	vec2 TexCoord;
}fs_in;


void main()
{
	float intensity = 1.0/ length(fs_in.position.xy - light_pos);
	vec4 texColor = texture(texture1, fs_in.TexCoord);
	if(texColor.a <0.1)
		discard;
	color = texColor;//* intensity;
}
