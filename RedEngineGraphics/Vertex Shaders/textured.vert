#version 330 core

layout (location = 0) in vec3 aPos; //Pixels
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec2 uResolution;
uniform mat3 uModelMat;
uniform mat3 uViewMat;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
	
	vec3 newPos = aPos * uModelMat * uViewMat;
	vec2 normalizedPosition = newPos.xy / uResolution;
	vec2 offsetPosition = (normalizedPosition * 2.0f - 1.0f); //Makes the bottom left (0,0)

	vColor = aColor;
	vTexCoord = aTexCoord;
	
	gl_Position = vec4(offsetPosition, aPos.z, 1.0f);
}