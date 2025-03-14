#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 vTexCoords;

uniform mat4 uProjMat;
uniform mat4 uViewMat;

void main()
{
	vTexCoords = aPos;
	gl_Position = uProjMat * uViewMat * vec4(aPos, 1.0);
}