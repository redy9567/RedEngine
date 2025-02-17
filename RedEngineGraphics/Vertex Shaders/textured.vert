#version 330 core

layout (location = 0) in vec3 aPos; //Pixels
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec2 uResolution;
uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

out vec3 vColor;
out vec2 vTexCoord;

void main()
{
	

	//vec3 newPos = uModelMat * aPos;

	//vec3 adjustedZ = newPos;
	//adjustedZ.z = -1.0f;

	vec4 newPos4 = uProjMat * uViewMat * uModelMat * vec4(aPos.xyz, 1.0f);
	//vec2 normalizedPosition = newPos.xy / uResolution;
	//vec2 offsetPosition = (normalizedPosition * 2.0f - 1.0f); //Makes the bottom left (0,0)

	vColor = aColor;
	vTexCoord = aTexCoord;
	
	gl_Position = newPos4;
}