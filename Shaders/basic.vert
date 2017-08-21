
attribute vec3 a_position;

varying vec4 v_color;

uniform mat4 mvp;
uniform vec4 colorTint;

void main(){
	v_color = vec4(1.0);
	gl_Position = mvp * vec4(a_position, 1.0);
}
