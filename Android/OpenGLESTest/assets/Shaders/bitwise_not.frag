varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

//bitwise_not
void main()
{
	gl_FragColor = vec4(1.0) - texture2D(tex2, uv);
}

