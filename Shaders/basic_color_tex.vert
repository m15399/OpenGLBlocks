
attribute vec3 a_position;
attribute vec4 a_color;
attribute vec2 a_uv;

varying vec4 v_color;
varying vec2 v_uv;

uniform mat4 mvp;
uniform vec4 colorTint;

void main(){
	v_color = a_color / 255.0 * colorTint;
	v_uv = a_uv;
	gl_Position = mvp * vec4(a_position, 1.0);
}
