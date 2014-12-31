varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const float textureWidth = float(1080.0);
const float textureHeight = float(1920.0);

const int kernelSize = 5;

uniform vec2 uv_offset[kernelSize * kernelSize];


//erosion
void main(void)
{
    vec4 sample[kernelSize * kernelSize];
    vec4 minValue = vec4(1.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = texture2D(tex2, uv + uv_offset[i]);

        minValue = min(sample[i], minValue);

    }

    gl_FragColor = minValue;
    
}