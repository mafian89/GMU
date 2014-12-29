varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska
uniform bool depth;	

//bitwise_xor
void main()
{ 
	vec4 first = ((vec4(1.0)-texture2D(tex2,uv)) * (texture2D(tex,uv)));
	vec4 second = ((texture2D(tex2,uv)) * (vec4(1.0)-texture2D(tex,uv)));
	gl_FragColor = ( first + second);
}

