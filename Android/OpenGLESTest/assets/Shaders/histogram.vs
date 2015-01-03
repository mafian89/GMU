attribute vec2 vPosition;
attribute vec2 vUV; //Unused - empty

varying vec2 uv; //Unused - empty

uniform sampler2D tex;

const float textureWidth = float(1080.0); 
const float textureHeight = float(1920.0);

void main()
{
	//Misto gl_Vertex budu brat z attribute vec2 position
	vec2 tc = vec2(vPosition.x / textureWidth, vPosition.y / textureHeight);
	//Barvicka
	vec3 color = texture2D(tex, tc.st).rgb;
 	
	//Do grayscale - 0 - 1
	float greyscale = 0.299 * color.r + 0.587 * color.g + 0.114 * color.b;

	//Do jakeho binu, mi to flakne
	float Xposition = greyscale * 255.0;
	
	vec2 Vertex = vec2(0);
	//Prevod z prostoru 0,1 do prostoru -1,1
	Vertex.x = (Xposition - 256.0 / 2.0) / (256.0 / 2.0);

	//y = -1.0 protoze je to v NDC
	gl_Position = vec4(Vertex.x, -1.0, 0.0, 1.0);
}