#version 120

uniform float timeElapsed;
uniform sampler2DRect texture;

//generate a random value from four points
vec4 rand(){ 
	return fract(sin(dot(gl_FragCoord.xy ,vec2(12.9898,78.233))) * 43758.5453);
} 

void main() {
	//gl_TexCoord[0]
	vec2 texCoord = vec2((gl_TexCoord[0].s + (cos(timeElapsed + rand().x) + 1.0) * 0.5) * 100.0, gl_TexCoord[0].t * 200.0);
	vec4 tex = texture2DRect(texture, texCoord);
	// /(cos(timeElapsed) + 1.0) * 0.5
	gl_FragColor = vec4(tex.r, tex.g, tex.b, 1.0);
}