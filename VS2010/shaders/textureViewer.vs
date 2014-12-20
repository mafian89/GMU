attribute vec2 vPosition;
attribute vec2 vUV;

varying vec2 uv;

void main()
{
	gl_Position = vec4(vPosition,1.0,1.0);
	uv = vUV;
}