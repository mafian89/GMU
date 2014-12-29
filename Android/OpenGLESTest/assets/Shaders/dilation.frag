varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const float textureWidth = float(1080.0);
const float textureHeight = float(1920.0);

const int kernelSize = 3;


//dilation
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
		
    vec4 sample[kernelSize * kernelSize];
    vec4 maxValue = vec4(0.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = texture2D(tex2, uv + uv_offset[i]);

        maxValue = max(sample[i], maxValue);

    }

    gl_FragColor = maxValue;
    
}