#version 330 core

out vec4 FragColor;

uniform sampler2D uTexture0;

in vec3 vColor;
in vec2 vTexCoord;

void main()
{
	vec4 ColorVal = vec4(vColor.xyz, 1.0f);
	FragColor = texture(uTexture0, vTexCoord) * ColorVal;
}