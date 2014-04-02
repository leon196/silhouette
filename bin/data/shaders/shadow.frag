#version 120

uniform float timeElapsed;
uniform sampler2DRect fboTexture;

//generate a random value from four points
vec4 rand(){ 
	return fract(sin(dot(gl_TexCoord[0].xy ,vec2(12.9898,78.233))) * 43758.5453);
} 


void main() {
	
	vec4 tex = texture2DRect(fboTexture,  gl_TexCoord[0].st * 800.0);
	//vec2(gl_TexCoord[0].s * 200.0, gl_TexCoord[0].t * 200.0));
	float osc = cos(timeElapsed);//(cos(timeElapsed) + 1.0) * 0.5;
	vec2 texCoord = vec2(gl_TexCoord[0].s + rand().x * 0.01 * osc, gl_TexCoord[0].t);//(cos(timeElapsed + rand().x) + 1.0) * 0.5) * 0.05, gl_TexCoord[0].t);
	float grid = step(mod(texCoord.t * 800.0, 20.0), 1.0) + step(mod(texCoord.s * 800.0, 20.0), 1.0);
	//step(mod(gl_TexCoord[0].t * 800.0, 20.0), 1.0) + step(mod(gl_TexCoord[0].s * 800.0, 20.0), 1.0);
	gl_FragColor = vec4(grid, 0.0, 0.0, grid);
	//vec4(vec3(0.0), tex.a) + vec4(vec3(0.0), 1.0 - step((tex.r + tex.g + tex.b) / 3., 0.1));
	// vec4(vec3(step((tex.r+tex.g+tex.b)/3., 0.01)), 1.0) + vec4(vec3(0.3), 1.0);
}