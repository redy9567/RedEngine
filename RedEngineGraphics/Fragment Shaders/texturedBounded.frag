#version 330 core

out vec4 FragColor;

uniform sampler2D uTexture0;


in vec3 vColor;
in vec2 vTexCoord;
in vec2 vPos;

in vec2 vLowerBound;
in vec2 vUpperBound;

void main()
{
	if( vLowerBound == vec2(0.0f, 0.0f) && vUpperBound == vec2(0.0f, 0.0f)
	|| (vPos.x > vLowerBound.x && vPos.x < vUpperBound.x) && (vPos.y > vLowerBound.y && vPos.y < vUpperBound.y))
	{
		vec4 tex = texture(uTexture0, vTexCoord);
		FragColor = tex;
	}
	else
	{
		FragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
	}

	
}