#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform vec2 uResolution;
uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

out vec3 vColor;

void main()
{
	vColor = aColor;
	gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos.xyz, 1.0f);
}