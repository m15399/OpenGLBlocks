
varying vec4 v_color;

float near = 20.0;
float far = 100.0;

float LinearizeDepth(float depth){
	float z = depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main(){
	gl_FragColor = v_color;

/*
	gl_FragColor = vec4(vec3(LinearizeDepth(gl_FragCoord.z) / far), 1.0);
*/

}
