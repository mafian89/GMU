varying vec2 uv;

uniform sampler2D tex;
uniform sampler2D tex2;

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

void main()
{
	gl_FragColor = texture2D(tex2, uv);
}