varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska
uniform bool depth;	

//bitwise_not
void main()
{
	gl_FragColor = vec4(1.0) - texture2D(tex2, uv);
}

