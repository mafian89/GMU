varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const int kernelSize = 5;

uniform vec2 uv_offset[kernelSize * kernelSize];

//mean filter
void main(void)
{
	
    vec4 colorSum = vec4(0.0);
	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		colorSum += texture2D(tex, uv + uv_offset[i]);
	}

    gl_FragColor = vec4(colorSum / float(kernelSize * kernelSize));
    
}