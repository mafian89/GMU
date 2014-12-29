varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska
uniform bool depth;	

//bitwise_or
void main()
{
	gl_FragColor = texture2D(tex2, uv) + texture2D(tex,uv);
}

