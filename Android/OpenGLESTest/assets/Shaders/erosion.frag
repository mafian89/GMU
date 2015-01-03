varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska


const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

//erosion
void main(void)
{
    vec4 sample[kernelSize * kernelSize];
    vec4 minValue = vec4(1.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = texture2D(tex2, uv + uv_offset3[i]);

        minValue = min(sample[i], minValue);

    }

    gl_FragColor = minValue;
    
}