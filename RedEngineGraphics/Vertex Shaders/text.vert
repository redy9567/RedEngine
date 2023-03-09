#version 330 core
layout (location = 0) in vec4 vertex; // <Vec2 pos, Vec2, tex)
out vec2 TexCoords;

uniform vec2 uResolution;

void main()
{
	vec2 normalizedPosition = vertex.xy / uResolution;
	gl_Position = vec4(normalizedPosition, 0.0, 1.0f);
	TexCoords = vertex.zw;
}