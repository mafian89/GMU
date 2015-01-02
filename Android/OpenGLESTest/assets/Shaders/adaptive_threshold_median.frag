varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const float minValue = 0.0;
const float maxValue = 1.0;

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

const int valueC = 10;

vec4 result;

/////////////////////////////
// Adaptive threshold type //
//  1 - mean 			   //
//  2 - (mean - valueC)    //	
//  3 - median 			   //
//  4 - (min + max) / 2    //	
/////////////////////////////
const int thresholdType = 3; 
const bool inverseThreshold = false;


/*float median(float sample[kernelSize * kernelSize])
{
	float tmp;
	int midIndex = int(((kernelSize * kernelSize)-1)/2);

	//sort array
	for (int n = ((kernelSize * kernelSize) - 1); n > 0; --n) 
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

//adaptive threshold
void main(void)
{		
    float sample[kernelSize * kernelSize];
    float minValueSample = float(1.0);
    float maxValueSample = float(0.0);
    float sampleSum = float(0.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = dot(texture2D(tex, uv + uv_offset3[i]).rgb, vec3(0.299, 0.587, 0.114));

        minValueSample = min(sample[i], minValueSample);
        maxValueSample = max(sample[i], maxValueSample);
        sampleSum += sample[i];

    }

    //evaluate threshold
    int threshold;

    if(thresholdType == 1) {        //mean
		threshold = int((sampleSum / float(kernelSize * kernelSize))*255.0);
	}
	else if (thresholdType == 2) {  //mean + C
    	threshold = int((sampleSum / float(kernelSize * kernelSize))*255.0) - valueC;
    }
    else if (thresholdType == 3) {  //median
    
		float tmp;
		int midIndex = int(((kernelSize * kernelSize)-1)/2);
		int n, i;
	
		//sort array
	/*	for (n = ((kernelSize * kernelSize) - 1); n > 0; --n) 
		{
	  		for (i = 0; i < n; ++i) 
	  		{ 
				tmp = min(sample[i], sample[i+1]); 
				sample[i+1] = sample[i] + sample[i+1] - tmp; 
				sample[i] = tmp; 
			}
		}
	*/
	
		n = 8;
		i = 0;
		while (n != 0)
		{
			tmp = min(sample[i], sample[i+1]); 
			sample[i+1] = sample[i] + sample[i+1] - tmp; 
			sample[i] = tmp;
			i++;
			
			if (i == n)
			{
				i = 0;
				n = n - 1;
			}
		}	
    
    	threshold = int( sample[midIndex] * 255.0); 
    }
    else if (thresholdType == 4) {  //(min+max)/2
    	threshold = int(((minValueSample + maxValueSample)/2.0) * 255.0);
    }

    float grey = dot(texture2D(tex, uv).rgb, vec3(0.299, 0.587, 0.114));
    int greyInt = int(grey * 255.0);

    if (greyInt >= threshold) 
    {
    	if (! inverseThreshold) {
    		grey = maxValue;
    	}
    	else {
    		grey = minValue;
    	}
    }
    else 
    {
    	if (! inverseThreshold) {
    		grey = minValue;
    	}
    	else {
    		grey = maxValue;
    	}
    	
    }
    
    gl_FragColor = vec4(vec3(grey),1.0);
    
    //result = vec4(vec3(grey),1.0);
}