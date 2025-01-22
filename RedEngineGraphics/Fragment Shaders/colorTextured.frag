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
	vec4 mixedColor = mix(tex, uColor, 0.5f);
	mixedColor.a = tex.a;
	FragColor = mixedColor;
}