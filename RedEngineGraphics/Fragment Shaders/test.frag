#version 330 core

out vec4 FragColor;

uniform float uTime;
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

in vec3 vColor;
in vec2 vTexCoord;

void main()
{
	float sinVal = (sin(uTime) / 2.0f) + 0.5f;
	vec4 ColorVal = vec4(vColor.r, vColor.g, vColor.b - sinVal, 1.0f);

	FragColor = mix(texture(uTexture0, vTexCoord), texture(uTexture1, vTexCoord), 0.5f) * ColorVal;
}