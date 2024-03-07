const char* const vertexMVP = R"(
	#version 330				// Shader 3.3
	precision highp float;		// normal floats, makes no difference on desktop computers
	
	uniform mat4 MVP;			// uniform variable, the Model-View-Projection transformation matrix
	layout(location = 0) in vec3 vp;	// Varying input: vp = vertex position is expected in attrib array 0
	layout(location = 1) in vec3 vc;
	out vec3 color;

	void main() {
		gl_Position = vec4(vp.x, vp.y, 0, 1) * MVP;		// transform vp from modeling space to normalized device space
		color = vc;
	}
)";