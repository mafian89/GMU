varying vec2 uv;

uniform sampler2D tex;
uniform sampler2D tex2;
uniform bool depth;

const int kernelSize = 3;

uniform vec2 uv_offset[kernelSize * kernelSize];

//bitwise_and
void main()
{
	gl_FragColor = texture2D(tex, uv) * texture2D(tex2,uv);
}

