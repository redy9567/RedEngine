#version 330 core

layout (location = 0) in vec3 aPos; //Pixels
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform vec2 uResolution;
uniform mat3 uModelMat;
uniform mat3 uViewMat;

uniform vec2 uLowerBound;
uniform vec2 uUpperBound;

out vec3 vColor;
out vec2 vTexCoord;
out vec2 vPos;

out vec2 vLowerBound;
out vec2 vUpperBound;

vec2 transformPoint(vec3 point)
{
	vec3 newPos = point * uModelMat * uViewMat;
	return newPos.xy;
}

vec2 normalizePoint(vec2 point)
{
	vec2 normalizedPosition = point / uResolution;
	return (normalizedPosition * 2.0f - 1.0f); //Makes the bottom left (0,0)
}

void main()
{
	
	vec2 offsetPosition = normalizePoint(transformPoint(aPos));

	vLowerBound = normalizePoint(uLowerBound);
	vUpperBound = normalizePoint(uUpperBound);

	vColor = aColor;
	vTexCoord = aTexCoord;
	vPos = offsetPosition;
	
	gl_Position = vec4(offsetPosition, aPos.z, 1.0f);
}