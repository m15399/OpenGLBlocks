
attribute vec4 a_position;
attribute vec4 a_color;
attribute float a_vOffset;

varying vec4 v_color;

uniform mat4 mvp;
uniform vec4 colorTint;

void main(){
	v_color = a_color / 255.0 * colorTint;
	vec4 pos = a_position;
	pos.z += a_vOffset;
	gl_Position = mvp * pos;
}
