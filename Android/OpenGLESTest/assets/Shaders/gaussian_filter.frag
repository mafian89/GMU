varying vec2 uv;

uniform sampler2D tex;      //textura
uniform sampler2D tex2;     //maska

const int kernelSize = 5;

uniform vec2 uv_offset[kernelSize * kernelSize];

/*const float gaussian[49] = float[49](0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036, 
									 0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363, 
									 0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,  
									 0.002291, 0.023226, 0.092651, 0.146768, 0.092651, 0.023226, 0.002291,  
									 0.001446, 0.014662, 0.058488, 0.092651, 0.058488, 0.014662, 0.001446,  
									 0.000363, 0.003676, 0.014662, 0.023226, 0.014662, 0.003676, 0.000363, 
									 0.000036, 0.000363, 0.001446, 0.002291, 0.001446, 0.000363, 0.000036); */
									 
  
//gaussian filter
void main(void)
{
       
    vec4 sample[kernelSize * kernelSize];

    for (int i = 0; i < (kernelSize * kernelSize); i++) 
    {
        sample[i] = texture2D(tex, uv + uv_offset[i]);
    }
    
    //Gaussian 3x3
   /* gl_FragColor = ((0.04 * (sample[0] + sample[2] + sample[6] + sample[8]))+
    				(0.12 * (sample[1] + sample[3] + sample[5] + sample[7]))+
    				(0.36 * sample[4]));*/
    
    //Gaussian 5x5			
	gl_FragColor = (
                   (0.00366  * (sample[0] + sample[4]  + sample[20] + sample[24])) +
                   (0.01465  * (sample[1] + sample[3]  + sample[5]  + sample[9] + sample[15] + sample[19] + sample[21] + sample[23])) +
                   (0.02564  * (sample[2] + sample[10] + sample[14] + sample[22])) +
                   (0.05861 * (sample[6] + sample[8]  + sample[16] + sample[18])) +
                   (0.09524 * (sample[7] + sample[11] + sample[13] + sample[17])) +
                   (0.15018 * sample[12])
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