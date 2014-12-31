varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

/*vec4 median(vec4 sample[kernelSize * kernelSize])
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
}*/

//median filter
void main(void)
{
	
    vec4 sample[kernelSize * kernelSize];

	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		sample[i] = texture2D(tex, uv + uv_offset3[i]);
	}
	
	int midIndex = int(((kernelSize * kernelSize)-1)/2);

    //gl_FragColor = vec4( median(sample) );
    //gl_FragColor = vec4( median(sample).rgb, 1.0 );
    gl_FragColor = vec4( sample[midIndex] );
    
}