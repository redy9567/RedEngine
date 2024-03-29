#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
	FragColor = vec4(textColor, texture(text, TexCoords).r);
}