varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const float textureWidth = float(800.0);
const float textureHeight = float(600.0);

const int threshold = 127;

//Fixed assigment of float value (1.0) to integer!!
const int minValue = 0;
const int maxValue = 1;


//threshold
void main(void)
{

    //greyscale image
    float grey = dot(texture2D(tex, uv).rgb, vec3(0.299, 0.587, 0.114));
	
    int greyInt = int(grey * 255.0);
	
	//Fixed Cast int into float!!
    if (greyInt >= threshold) 
    {
    	grey = float(maxValue);
    }
    else 
    {
    	grey = float(minValue);
    }
    

    gl_FragColor = vec4(grey);
    
}