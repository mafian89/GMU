varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 5;

uniform vec2 uv_offset[kernelSize * kernelSize];


//dilation
void main(void)
{
    vec4 sample[kernelSize * kernelSize];
    vec4 maxValue = vec4(0.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = texture2D(tex2, uv + uv_offset[i]);

        maxValue = max(sample[i], maxValue);

    }

    gl_FragColor = maxValue;
    
}