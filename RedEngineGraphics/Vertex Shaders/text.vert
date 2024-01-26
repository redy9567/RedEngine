#version 330 core
layout (location = 0) in vec4 vertex; // Vertex should be normalized screen coordinates [0,1]
out vec2 TexCoords;

uniform vec2 uResolution;

void main()
{
	vec2 normalizedPosition = vertex.xy;
	vec2 offsetPosition = (normalizedPosition * 2.0f - 1.0f) ; //Makes the bottom left (0,0) pre-shader (Translate's to OpenGL's [-1, 1])

	gl_Position = vec4(offsetPosition, 0.0, 1.0f);
	TexCoords = vertex.zw;
}