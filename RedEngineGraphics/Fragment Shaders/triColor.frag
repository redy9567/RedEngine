#version 330 core
out vec4 FragColor;
in vec2 FragCoord;

void main()
{

	if(FragCoord.x > 50)
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	else
		FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);

}