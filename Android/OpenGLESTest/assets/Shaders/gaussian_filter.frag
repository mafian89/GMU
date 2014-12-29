varying vec2 uv;

uniform sampler2D tex;      //textura
uniform sampler2D tex2;     //maska

uniform bool depth; 

const float textureWidth = float(1080.0);
const float textureHeight = float(1920.0);

const int kernelSize = 3;


// 1  4  7  4 1
// 4 16 26 16 4
// 7 26 41 26 7 / 273 (i.e. divide by total of weightings)
// 4 16 26 16 4
// 1  4  7  4 1
//const float gaussian[25] = float[25](1.0, 4.0, 7.0, 4.0, 1.0, 4.0, 16.0, 26.0, 16.0, 
//                            4.0, 7.0, 26.0, 41.0, 26.0, 7.0, 4.0, 16.0, 26.0, 16.0, 4.0, 1.0, 4.0, 7.0, 4.0, 1.0);
//const float gaussianSum = 273.0;


//1 3 1
//3 9 3 / 25 
//1 3 1
const float gaussian[9] = float[9](1.0, 3.0, 1.0, 3.0, 9.0, 3.0, 1.0, 3.0, 1.0);
const float gaussianSum = 25.0;


//gaussian filter
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
    vec4 sum = vec4(0.0);


    for (int i = 0; i < (kernelSize * kernelSize); i++) 
    {
        sample[i] = texture2D(tex, uv + uv_offset[i]);

        sum += (sample[i] * gaussian[i]) ;
    }



    gl_FragColor = vec4(( sum.rgb / gaussianSum ),1.0);
    
    //gl_FragColor = vec4( sum  / gaussianSum);
    
}