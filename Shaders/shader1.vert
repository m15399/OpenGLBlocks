
attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec4 a_color;

varying vec4 v_color;

uniform mat4 mvp;
uniform vec4 colorTint;

void main(){
	vec3 lightDirection = vec3(1.0, -1.0, 1.0);
	float cosTheta = dot(a_normal, normalize(lightDirection));
	cosTheta = cosTheta + 1.0;
	cosTheta = clamp(cosTheta, 0.0, 1.0);

	vec4 outColor = a_color / 255.0 * colorTint;
	float a = outColor.a;
	outColor = outColor * cosTheta;
	outColor.a = a;

	v_color = outColor;

	gl_Position = mvp * vec4(a_position, 1.0);
}
