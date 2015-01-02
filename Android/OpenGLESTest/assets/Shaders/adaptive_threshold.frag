varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const float minValue = 0.0;
const float maxValue = 1.0;

const int kernelSize = 11;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

const int valueC = 10;

/////////////////////////////
// Adaptive threshold type //
//  1 - mean 			   //
//  2 - (mean - valueC)    //	
//  3 - median 			   //
//  4 - (min + max) / 2    //	
/////////////////////////////
const int thresholdType = 3; 
const bool inverseThreshold = false;

vec4 result;

float median(float sample[kernelSize * kernelSize])
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
}

//adaptive threshold
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
		
    float sample[kernelSize * kernelSize];
    float minValueSample = float(1.0);
    float maxValueSample = float(0.0);
    float sampleSum = float(0.0);

    for (int i = 0; i < (kernelSize * kernelSize); i++)
    {
        sample[i] = dot(texture2D(tex, uv + uv_offset11[i]).rgb, vec3(0.299, 0.587, 0.114));

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
    	threshold = int( median(sample) * 255.0); 
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