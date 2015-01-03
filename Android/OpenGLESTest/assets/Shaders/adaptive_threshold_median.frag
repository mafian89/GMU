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

/////////////////////////////
// Adaptive threshold type //
//  1 - mean 			   //
//  2 - (mean - valueC)    //	
//  3 - median 			   //
//  4 - (min + max) / 2    //	
/////////////////////////////
const int thresholdType = 3; 
const bool inverseThreshold = false;

float temp, a, b;

#define s2(a, b) temp = a; a = min(a, b); b = max(temp, b);
#define mn3(a, b, c) s2(a, b); s2(a, c);
#define mx3(a, b, c) s2(b, c); s2(a, c);

#define mnmx3(a, b, c) mx3(a, b, c); s2(a, b); // 3 exchanges
#define mnmx4(a, b, c, d) s2(a, b); s2(c, d); s2(a, c); s2(b, d); // 4 exchanges
#define mnmx5(a, b, c, d, e) s2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e); // 6 exchanges
#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); mn3(a, b, c); mx3(d, e, f); // 7 exchanges


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
		mnmx6(sample[0], sample[1], sample[2], sample[3], sample[4], sample[5]);
		mnmx5(sample[1], sample[2], sample[3], sample[4], sample[6]);
		mnmx4(sample[2], sample[3], sample[4], sample[7]);
		mnmx3(sample[3], sample[4], sample[8]);
    	threshold = int( sample[4] * 255.0); 
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
}