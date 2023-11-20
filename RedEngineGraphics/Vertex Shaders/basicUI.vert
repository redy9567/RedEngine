#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 uResolution;

void main()
{
	vec2 normalizedPosition = aPos.xy / uResolution;
	vec2 offsetPosition = (normalizedPosition * 2.0f - 1.0f) ; //Makes the bottom left (0,0)

	gl_Position = vec4(offsetPosition, 0.0, 1.0f);
	
}