varying vec2 uv;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	//gl_FragColor = texture2D(tex, uv) * texture2D(tex2,uv);
	gl_FragColor = vec4(0.0,1.0,0.0,1.0);
}