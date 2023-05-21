#version 330 core

out vec4 FragColor;

uniform sampler2D uTexture0;
uniform vec4 uColor;

in vec3 vColor;
in vec2 vTexCoord;

void main()
{
	vec4 ColorVal = vec4(vColor.xyz, 1.0f);
	vec4 tex = texture(uTexture0, vTexCoord);

	FragColor = (dot(tex, vec4(1.0f, 1.0f, 1.0f, 1.0f)) > 3.5f) ? vec4(tex.r, uColor.gb, tex.a) : tex;

	float val = dot(tex, vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//FragColor = (val > 3.5f) ? vec4(tex.r, uColor.gb, tex.a) : ((val > 2.4f && val < 2.7f) ? vec4(0.0f, 0.0f, 1.0f, 1.0f) : tex);
}