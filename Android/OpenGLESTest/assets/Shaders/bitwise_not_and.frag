varying vec2 uv;

uniform sampler2D tex;		//textura
uniform sampler2D tex2;		//maska
uniform bool depth;	

//bitwise_not + texture
void main()
{
	gl_FragColor = texture2D(tex,uv) * (vec4(1.0) - texture2D(tex2, uv));
}

