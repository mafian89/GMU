varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska

const int kernelSize = 3;

uniform vec2 uv_offset3[9];
uniform vec2 uv_offset5[25];
uniform vec2 uv_offset11[121];

vec4 temp, a, b;

#define s2(a, b) temp = a; a = min(a, b); b = max(temp, b);
#define mn3(a, b, c) s2(a, b); s2(a, c);
#define mx3(a, b, c) s2(b, c); s2(a, c);

#define mnmx3(a, b, c) mx3(a, b, c); s2(a, b); // 3 exchanges
#define mnmx4(a, b, c, d) s2(a, b); s2(c, d); s2(a, c); s2(b, d); // 4 exchanges
#define mnmx5(a, b, c, d, e) s2(a, b); s2(c, d); mn3(a, c, e); mx3(b, d, e); // 6 exchanges
#define mnmx6(a, b, c, d, e, f) s2(a, d); s2(b, e); s2(c, f); mn3(a, b, c); mx3(d, e, f); // 7 exchanges

//median filter
void main(void)
{
    vec4 sample[kernelSize * kernelSize];

	for (int i = 0; i < (kernelSize * kernelSize); i++) 
	{
		sample[i] = texture2D(tex, uv + uv_offset3[i]);
	}
	
    mnmx6(sample[0], sample[1], sample[2], sample[3], sample[4], sample[5]);
	mnmx5(sample[1], sample[2], sample[3], sample[4], sample[6]);
	mnmx4(sample[2], sample[3], sample[4], sample[7]);
	mnmx3(sample[3], sample[4], sample[8]);
    
    gl_FragColor = vec4( sample[4] );
}