#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;
in DATA
{
	vec4 position;
	vec4 Ocolor;
	float tid;
	vec2 TexCoord;
}fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0/ length(fs_in.position.xy - light_pos);
	vec4 texColor = fs_in.Ocolor;
	if(fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid);
		texColor = texture(textures[1], fs_in.TexCoord);
	}
	if(texColor.a <0.1)
		discard;
	color = texColor;//* intensity;
}
