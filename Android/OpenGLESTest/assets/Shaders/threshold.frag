varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

uniform bool depth;	

const float textureWidth = float(1080.0);
const float textureHeight = float(1920.0);

const int threshold = 127;

const float minValue = 0.0;
const float maxValue = 1.0;

const bool inverseTresh = true;

const int kernelSize = 5;

uniform vec2 uv_offset[kernelSize * kernelSize];

//threshold
void main(void)
{

    //greyscale image
    float grey = dot(texture2D(tex, uv).rgb, vec3(0.299, 0.587, 0.114));

    int greyInt = int(grey * 255.0);

    if (greyInt >= threshold) 
    {   
        if (! inverseTresh) {
            grey = maxValue;
        }
        else {
            grey = minValue;
        }
    }
    else 
    {
    	if (! inverseTresh) {
            grey = minValue;
        }
        else {
            grey = maxValue;
        }
    }
    

    gl_FragColor = vec4(grey);
    
}