#version 120

// varying vec4 vFragColor;
// uniform sampler2DRect fboTexture;
varying vec2 vTexCoord;

void main() {
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	//float oscX = (cos(timeValX + gl_TexCoord[0].s * 800.0) + 1.0) * 0.5;
	//float oscY = (sin(timeValX + gl_TexCoord[0].t * 800.0) + 1.0) * 0.5;
	vTexCoord = vec2(gl_TexCoord[0].s, gl_TexCoord[0].t);
	//vTexCoord = gl_TexCoord[0].st; 

	//get our current vertex position so we can modify it
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;

	//finally set the pos to be that actual position rendered
	gl_Position = pos;

	gl_FrontColor = gl_Color;
}