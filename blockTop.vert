
attribute vec4 a_position;
attribute vec4 a_color;
attribute float a_boneIndex;

varying vec4 v_color;

uniform mat4 mvp;
uniform vec4 colorTint;
uniform vec4 vOffsets[32 * 32 / 4];

void main(){
	v_color = a_color / 255.0 * colorTint;
	vec4 pos = a_position;

	int index1 = int(a_boneIndex / 4.0);
	int index2 = int(mod(a_boneIndex, 4.0));
	pos.z += vOffsets[index1][index2];
	
	gl_Position = mvp * pos;
}
