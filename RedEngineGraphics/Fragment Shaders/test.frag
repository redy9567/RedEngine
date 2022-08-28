#version 330 core

out vec4 FragColor;

uniform float uTime;

void main()
{
	float sinVal = (sin(uTime * 4) / 2.0f) + 0.5f;

	FragColor = vec4(sinVal, sinVal, 1.0f, 1.0f);
}