attribute vec2 vPosition;

uniform sampler2D tex;

uniform float textureWidth;
uniform float textureHeight;

void main()
{
	//Vypocet texturovacich souradnic
	vec2 tc = vec2(vPosition.x / textureWidth, vPosition.y / textureHeight);
	//Ziskani barvy pixelu
	vec3 color = texture2D(tex, tc).rgb;
 	
	//Do grayscale - 0 - 1
	float greyscale = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;

	//Pozice v 0 - 255
	float Xposition = greyscale * 255.0;
	
	vec2 Vertex = vec2(0);
	//Prevod z prostoru 0,1 do prostoru -1,1
	Vertex.x = (Xposition - textureWidth / 2.0) / (textureWidth / 2.0);

	//zapiseme do "binu" v histogramu
	gl_Position = vec4(Vertex.x, -1.0, 0.0, 1.0);
}