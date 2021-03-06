#version 120

varying vec2 vTexCoord;
// varying vec4 vFragColor;
uniform sampler2DRect fboTexture;
uniform sampler2DRect depthTexture;
uniform float timeValX;


////////////////////// KERNEL FILTERING ////////////////
vec4 image_processing(vec2 decalCoords, sampler2DRect decal)
{
	int filter[9] =  int[](0,   -1,   0, -1,   4,   -1,  0,   -1,   0);
	vec4 color = vec4(0);

	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++) {
			vec4 tex = texture2DRect(decal, decalCoords + vec2(i-1,j-1));;
			color += filter[i+j*3] * step(1.0 - (tex.r + tex.g + tex.b) / 3.0, 0.001);
		}								
	}

	float col = (color.r + color.g + color.b) / 3.0;
	color.rgb = vec3(1.0 - step(col, 0.01));
	color.a = texture2DRect(decal, decalCoords).a;
	return (color);
}

void main() {
	//we grab the x and y and store them in an int
	// float xVal = gl_FragCoord.x;
	// float yVal = gl_FragCoord.y;

	vec2 texCoord = vec2(gl_FragCoord.s, 800.0 - gl_FragCoord.t);
	
	// gl_FragColor = vFragColor;
	vec4 tex = texture2DRect(fboTexture, texCoord);
	vec4 texDepth = texture2DRect(depthTexture, texCoord);
	vec4 edges = image_processing(texCoord, depthTexture);
	// float col = tex.r + tex.g + tex.b;
	float osc = (cos(timeValX) + 1.0) * 0.5;
	//float a = step(1.0 - (tex.r + tex.g + tex.b) / 3.0, 0.001);
	gl_FragColor = vec4(0.0, edges.r, 0.0, edges.r);
	// gl_FragColor = vec4(texCoord.y / 600.0, 0.0, 0.0, 1.0);
}