varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const float textureWidth = float(800.0);
const float textureHeight = float(600.0);

const int kernelSize = 5;

//mean filter
void main(void)
{

	vec2 uv_offset[kernelSize * kernelSize];
	float xInc = 1.0 / float(textureWidth);
	float yInc = 1.0 / float(textureHeight);

	//plnime offset
	for (int i = 0; i < kernelSize; i++) 
	{
		for (int j = 0; j < kernelSize; j++) 
		{
			uv_offset[((i*kernelSize)+j)] = vec2( ((-1.0 * xInc) + (float(i) * xInc)) , ((-1.0 * yInc)+(float(j) * yInc)) );
		}

	}	
		
    vec4 colorSum = vec4(0.0);
	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		colorSum += texture2D(tex, uv + uv_offset[i]);
	}

    gl_FragColor = vec4(colorSum / float(kernelSize * kernelSize));
    
}