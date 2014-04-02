#version 120

uniform float timeElapsed = 1.0;

void main() {
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	gl_Position = pos;// + vec4(cos(timeElapsed + gl_TexCoord[0].x * 10.0) * 200.0, 0.0, 0.0, 0.0);//vec4(pos.x + cos(timeElapsed) * 20.0, pos.y, pos.z, pos.w);
	gl_FrontColor = gl_Color;
}