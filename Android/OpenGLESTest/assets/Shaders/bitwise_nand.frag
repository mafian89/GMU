varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska
uniform bool depth;	

const int kernelSize = 3;

uniform vec2 uv_offset[kernelSize * kernelSize];

//bitwise_not + and
void main()
{
	gl_FragColor = texture2D(tex,uv) * (vec4(1.0) - texture2D(tex2, uv));
}

