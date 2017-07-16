
attribute vec4 a_position;
attribute vec4 a_color;

varying vec4 v_color;

uniform mat4 mvp;
uniform vec4 colorTint;

void main(){
	v_color = a_color / 255.0 * colorTint;
	gl_Position = mvp * a_position;
}
