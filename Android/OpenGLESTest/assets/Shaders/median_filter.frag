varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const float textureWidth = float(1080.0);
const float textureHeight = float(1920.0);

const int kernelSize = 3;

vec4 median(vec4 sample[kernelSize * kernelSize])
{
    vec4 tmp;
    int midIndex = int(((kernelSize * kernelSize)-1)/2);

    //sort array
    for (int n = ((kernelSize * kernelSize) - 1) ; n > 0 ; --n) 
    {
        for (int i = 0; i < n; ++i) 
        { 
            tmp = min(sample[i], sample[i+1]); 
            sample[i+1] = sample[i] + sample[i+1] - tmp; 
            sample[i] = tmp; 
        }
    }

    return sample[midIndex];
}

//median filter
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

	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		sample[i] = texture2D(tex, uv + uv_offset[i]);
	}
	
	int midIndex = int(((kernelSize * kernelSize)-1)/2);

    gl_FragColor = vec4( median(sample) );
    //gl_FragColor = vec4( median(sample).rgb, 1.0 );
    //gl_FragColor = vec4( sample[midIndex] );
    
}