varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 11;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

//mean filter
void main(void)
{
	
    vec4 colorSum = vec4(0.0);
	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		colorSum += texture2D(tex, uv + uv_offset11[i]);
	}

    gl_FragColor = vec4(colorSum / float(kernelSize * kernelSize));
}