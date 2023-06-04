#version 330 core

out vec4 FragColor;

uniform sampler2D uTexture0;
uniform vec4 uColor;

in vec3 vColor;
in vec2 vTexCoord;

vec3 convertRGBtoHSV(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 convertHSVtoRGB(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec4 tex = texture(uTexture0, vTexCoord);

    vec3 hueColor = convertRGBtoHSV(uColor.xyz);
    vec3 texHSV = convertRGBtoHSV(tex.xyz);

    vec4 finalColor = vec4(convertHSVtoRGB(vec3(hueColor.xy, texHSV.z)), tex.w);
    
    FragColor = finalColor;
}