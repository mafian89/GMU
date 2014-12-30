varying vec2 uv; //UNUSED

uniform sampler2D tex;		//textura - UNUSED
uniform sampler2D tex2;		//maska - UNUSED


const float textureWidth = float(1080.0); //UNUSED
const float textureHeight = float(1920.0);//UNUSED

const int threshold = 127; //UNUSED

const float minValue = 0.0;//UNUSED
const float maxValue = 1.0;//UNUSED

const bool inverseTresh = true;//UNUSED


//threshold
void main(void)
{
    gl_FragColor = vec4(1.0/255.0, 1.0/255.0, 1.0/255.0, 1.0);
    
}