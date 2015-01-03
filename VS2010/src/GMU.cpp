#include "common.h"
#include "CTextureViewer.h"

//error LNK2019: unresolved external symbol _main referenced in function ___tmainCRTStartup
#undef main
//or use sdlmain.lib

using namespace std;

#define WIDTH 256
#define HEIGHT 256

float aspect;
CTextureViewer * ctv;
GLuint tex, tex2,renderTex;
float arr[WIDTH*HEIGHT*2];
GLuint HistogramVBO, FBO;
GLSLShader hist;

int printed = 1;

void onInit();

///////////////////////////////////////////
// FUNCTIONS
///////////////////////////////////////////
struct SDL_Exception : public std::runtime_error
{
    SDL_Exception() throw()
        : std::runtime_error(std::string("SDL : ") + SDL_GetError()) {}
    SDL_Exception(const char * text) throw()
        : std::runtime_error(std::string("SDL : ") + text + " : " + SDL_GetError()) {}
    SDL_Exception(const std::string & text) throw()
        : std::runtime_error(std::string("SDL : ") + text + " : " + SDL_GetError()) {}
};

SDL_Surface * init(unsigned width, unsigned height, unsigned color, unsigned depth, unsigned stencil)
{
    // Set OpenGL attributes
    if(SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, color) < 0) throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, depth) < 0) throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, stencil) < 0) throw SDL_Exception();
    if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) throw SDL_Exception();

    // Create window
    SDL_Surface * screen = SDL_SetVideoMode(width, height, color, SDL_OPENGL);
    if(screen == NULL) throw SDL_Exception();
    // Init extensions
    GLenum error = glewInit();
    if(error != GLEW_OK)
        throw std::runtime_error(std::string("GLEW : Init failed : ") + (const char*)glewGetErrorString(error));
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    // Call init code
    onInit();

    //onWindowResized(width, height);

    return screen;
}


void initPointVBO() {

	for(int i=0;i<WIDTH*HEIGHT;i++) {
		arr[2*i] = (float)(i % WIDTH);
		arr[2*i+1] = (float)((int)(i / WIDTH));
	}


	//Generate VBO
	glGenBuffers(1, &HistogramVBO);

	//Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, HistogramVBO);

	//Alocate buffer
	glBufferData(GL_ARRAY_BUFFER, 2*WIDTH*HEIGHT*sizeof(float), arr, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Fill VBO
	//glBufferSubData(GL_ARRAY_BUFFER, 0, 2*w*h*sizeof(float), arr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	/*for(int k=0; k < 16; k++) {
		DPRINTF("k:%d - %f %f",k,arr[2*k],arr[2*k + 1]);
	}*/
}

//DevIL
// Function load a image, turn it into a texture, and return the texture ID as a GLuint for use
// taken from: http://r3dux.org/tag/ilutglloadimage/
GLuint loadImage(const char* theFileName)
{
	ILuint imageID;				// Create an image ID as a ULuint

	GLuint textureID;			// Create a texture ID as a GLuint

	ILboolean success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilGenImages(1, &imageID); 		// Generate the image ID

	ilBindImage(imageID); 			// Bind the image

	success = ilLoadImage(theFileName); 	// Load the image file

	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		// Convert the image into a suitable format to work with
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			std::cout << "Image conversion failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
			exit(-1);
		}

		// Generate a new texture
		glGenTextures(1, &textureID);

		// Bind the texture to a name
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		// Specify the texture specification
		glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());			// The actual image data itself
	}
	else // If we failed to open the image file in the first place...
	{
		error = ilGetError();
		std::cout << "Image load failed - IL reports error: " << error << " - " << iluErrorString(error) << std::endl;
		exit(-1);
	}

	ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	std::cout << "Texture creation successful." << std::endl;

	return textureID; // Return the GLuint to the texture so you can use it!
}
//DevIL

void initTex() {
	//Render texture should have the same res as display
	glGenTextures (1, &renderTex);
	glBindTexture (GL_TEXTURE_2D, renderTex);
	glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB32F , 256, 1, 0, GL_RGB, GL_FLOAT, 0);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);*/
	glBindTexture(GL_TEXTURE_2D, 0);
}

void initHistogramFBO() {
	glGenFramebuffers (1, &FBO);
	glBindFramebuffer (GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D (GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTex, 0);

	// check FBO status
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	switch(status) {
	case GL_FRAMEBUFFER_COMPLETE_EXT:
		std::cout << "Framebuffer complete." << std::endl;
		break;
		//return true;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Attached images have different dimensions." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Color attached images have different internal formats." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
		std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
		break;

	case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
		std::cout << "[ERROR] Unsupported by FBO implementation." << std::endl;
		break;

	default:
		std::cout << "[ERROR] Unknow error." << std::endl;
		break;
	}

	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void computeHistogram() {
	glViewport(0, 0, WIDTH, HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glDisable(GL_DEPTH_TEST);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	//Additive
	glBlendEquation(GL_FUNC_ADD);
	
	hist.Use();

	glBindBuffer(GL_ARRAY_BUFFER, HistogramVBO);

	glVertexAttribPointer(hist["vPosition"], 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GL_FLOAT), (void*)0);
	glEnableVertexAttribArray(hist["vPosition"]);

	glUniform1i(hist("tex"), 0);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Compute histogram
	glDrawArrays(GL_POINTS, 0, WIDTH*HEIGHT);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	hist.UnUse();
	//Disable blending
	glDisable(GL_BLEND);

	float hPixels[256];
	glReadPixels(0, 0, 256, 1, GL_BLUE, GL_FLOAT, hPixels);

	int sum = 0;
	if (printed != 0) 
	{
		cout << "\n\n-----------\n\n";
		for(int j = 0; j < 256; j++)
		{
			//if((j % 3) == 0)
				cout << j << ":" << hPixels[j] << endl;
				sum += hPixels[j];
		}
		cout << endl << sum << endl;
		printed--;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void onInit() {
	//tex = loadImage("../textures/texture.png");
	tex = loadImage("../textures/sracka.png");
	tex2 = loadImage("../textures/sracka.png");
	ctv = new CTextureViewer(0, "../shaders/textureViewer.vs", "../shaders/textureViewer.frag");
	ctv->setTexture(tex);
	ctv->setTexture2(tex2);

	hist.LoadFromFile(GL_VERTEX_SHADER, "../shaders/histogram.vs");
	hist.LoadFromFile(GL_FRAGMENT_SHADER, "../shaders/histogram.frag");
	hist.CreateAndLinkProgram();

	hist.Use();

	//Create uniforms and attributes (filled later)
	hist.AddAttribute("vPosition");
	hist.AddUniform("tex");

	hist.UnUse();

	initTex();
	initPointVBO();
	initHistogramFBO();
}


void Display() {
	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Clear color
	glClearColor(0.0, 0.0, 0.6, 1.0);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//View port
	glViewport(0, 0, WIDTH, HEIGHT);
	//downsample
	//glViewport(0,0,width/2,height/2);
}

void DisplayTexture(CTextureViewer * ctv) {

	//glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	ctv->draw();

	//Swap buffers
	SDL_GL_SwapBuffers();
}
void Finalize(void) {
	delete ctv;
}
void Reshape(int width, int height){
	glViewport(0, 0, width, height);
	aspect = float(height) / float(width);
}


int main() {

	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);

	SDL_Surface *screen;
	int done;
	Uint8 *keys;
	//Initialize
	if(SDL_Init(SDL_INIT_VIDEO)< 0) throw SDL_Exception();
	SDL_EnableKeyRepeat(100,SDL_DEFAULT_REPEAT_INTERVAL);
	//Create a OpenGL window
	screen = init(256,256,24,24,8);
	//SDL_WM_SetCaption(WINDOW_TITLE, WINDOW_TITLE);

	const int FPS_limit = 60;
	// The main loop
	done = 0;

	while(!done) 
	{
		SDL_Event event;
		//Respond to any events that occur
		while(SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
				case SDL_QUIT:
					done = 1;
					break;
			}
		}
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex2);
		computeHistogram();
		DisplayTexture(ctv);
	}
	Finalize();
	// Clean up and quit
	SDL_Quit();
	return 0;
}

