attribute vec2 vPosition;
attribute vec2 vUV;

uniform int v_coord_flipped;

varying vec2 uv;

void main()
{
	gl_Position = vec4(vPosition,1.0,1.0);
	float v_coord;
	if(v_coord_flipped > 0) {
		v_coord = 1.0 - vUV.y;
	} else {
		v_coord = vUV.y;
	}
	uv = vec2(vUV.x,v_coord);
}