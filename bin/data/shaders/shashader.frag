#version 120

uniform float timeElapsed;
uniform sampler2DRect texture;

void main() {
	//gl_TexCoord[0]
	vec2 texCoord = vec2((gl_TexCoord[0].s + (cos(timeElapsed + gl_TexCoord[0].t) + 1.0) * 0.5) * 200.0, gl_TexCoord[0].t * 200.0);
	vec4 tex = texture2DRect(texture, texCoord);
	// /(cos(timeElapsed) + 1.0) * 0.5
	gl_FragColor = vec4(tex.r, tex.g, tex.b, 1.0);
}