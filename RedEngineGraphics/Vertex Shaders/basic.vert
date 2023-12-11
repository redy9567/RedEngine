#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 uResolution;
uniform mat3 uModelMat;
uniform mat3 uViewMat;

void main()
{
	vec3 newPos = aPos * uModelMat * uViewMat;
	vec2 normalizedPosition = newPos.xy / uResolution;
	vec2 offsetPosition = (normalizedPosition * 2.0f - 1.0f); //Makes the bottom left (0,0)

	
	gl_Position = vec4(offsetPosition, aPos.z, 1.0f);
	
}