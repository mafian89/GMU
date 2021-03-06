varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

//bitwise_xor
void main()
{ 
	vec4 first = ((vec4(1.0)-texture2D(tex2,uv)) * (texture2D(tex,uv)));
	vec4 second = ((texture2D(tex2,uv)) * (vec4(1.0)-texture2D(tex,uv)));
	gl_FragColor = ( first + second);

}

