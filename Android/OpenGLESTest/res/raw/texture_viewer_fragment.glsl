varying vec2 uv;

uniform sampler2D tex;
uniform sampler2D tex2;

void main()
{
	gl_FragColor = texture2D(tex, uv) * texture2D(tex2,uv);
}