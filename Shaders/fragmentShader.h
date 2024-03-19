const char *const fragmentDefault = R"(
	#version 330			// Shader 3.3
	precision highp float;	// normal floats, makes no difference on desktop computers
	
	//uniform vec3 color;		// uniform variable, the color of the primitive
	in vec3 color;
	out vec4 outColor;		// computed color of the current pixel

	void main() {
		outColor = vec4(color, 1);	// computed color is the color of the primitive
	}
)";

const char *const fragmentDnum = R"(
	#version 330
    	precision highp float;

	uniform vec4 color;			// uniform color
	out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

	void main() {
		fragmentColor = color; 
	}
)";

const char *const fragmentCurve = R"(
	#version 330
	precision highp float;
	uniform vec3 color;
	out vec4 outColor;
	void main() {
		outColor = vec4(color, 1);
	}
)";
