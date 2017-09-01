
varying vec4 v_color;
varying vec2 v_uv;

uniform sampler2D tex;

void main(){
	gl_FragColor = v_color * texture2D(tex, v_uv);
}
