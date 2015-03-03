varying vec2 uv;

uniform sampler2D tex;      //textura
uniform sampler2D tex2;     //maska

const int kernelSize = 5;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

uniform float uv_offset5_X[5];
uniform float uv_offset5_Y[5];
	
  
//gaussian filter
void main(void)
{
       
    vec4 sample[kernelSize];

    for (int i = 0; i < kernelSize; i++) 
    {
        sample[i] = texture2D(tex, vec2(float(uv.x + uv_offset5_X[i]),uv.y));
    }
    
    //Gaussian 3x3
   /* gl_FragColor = ((0.04 * (sample[0] + sample[2] + sample[6] + sample[8]))+
    				(0.12 * (sample[1] + sample[3] + sample[5] + sample[7]))+
    				(0.36 * sample[4]));
    */
    /*
    //Gaussian 5x5			
	gl_FragColor = (
                   (0.06136  * sample[0]) +
                   (0.24477  * sample[1]) +
                   (0.38774  * sample[2]) +
                   (0.24477  * sample[3]) +
                   (0.06136  * sample[4])
                   ) ; 
     */              
                   
    //Gaussian 5x5			
	gl_FragColor = (
                   (0.06050  * sample[0]) +
                   (0.24210  * sample[1]) +
                   (0.38753  * sample[2]) +
                   (0.24210  * sample[3]) +
                   (0.06050  * sample[4])
                   ) ;
  
                   
    //Gaussian 7x7
	/*gl_FragColor = (								 
 					(0.000036 * (sample[0] + sample[6] + sample[42] + sample[48])) +
					(0.000363 * (sample[1] + sample[5] + sample[7] + sample[13] + sample[35] + sample[41] + sample[43] + sample[47])) +
 					(0.001446 * (sample[2] + sample[4] + sample[14] + sample[20] + sample[28] + sample[34] + sample[44] + sample[46])) +
					(0.002291 * (sample[3] + sample[21] + sample[27] + sample[45])) +	
					(0.003676 * (sample[8] + sample[12] + sample[36] + sample[40])) +	
					(0.014662 * (sample[9] + sample[11] + sample[15] + sample[19] + sample[29] + sample[33] + sample[37] + sample[39])) +	
					(0.023226 * (sample[10] + sample[22] + sample[26] + sample[38])) +	
					(0.058488 * (sample[16] + sample[18] + sample[30] + sample[32])) +	
					(0.092651 * (sample[17] + sample[23] + sample[25] + sample[31])) +									 
					(0.146768 * sample[24])
				   );*/
													
}