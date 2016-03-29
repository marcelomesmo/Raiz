#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(std::string path, int sprite_width, int sprite_height, Color* transparent)
{
	create(path, sprite_width, sprite_height);
}
SpriteSheet::SpriteSheet()
{
}

SpriteSheet::~SpriteSheet()
{
}
void SpriteSheet::free()
{
	//Free texture if it exists
	if (image != NULL)
	{
		SDL_DestroyTexture(image);
		image = NULL;
		width = 0;
		height = 0;
	}
}

	/*
	*		    *************************************	
	*					Creating Sprite Sheet		
	*			*************************************
	*/
// Load Sprite Sheets using Sprites with the same size (in width and height)
bool SpriteSheet::create(std::string path, int sprite_width, int sprite_height, Color* transparent)
{
	// Create a Sprite with specified image path
	if(!initImage(path, transparent)) return false;

	/*	
		For SpriteSheets with Sprites that have the same size (in width and height):

		sheet width --->								sheet width --->
		________________					ex: 32x32	___________________
		| 1	   2    3   |   |					imgs	| 0,0  32,0  64,0  |	|
		| 4	   5	6	|	| sheet height				| 0,32 32,32 64,32 |	| sheet height
		|_7____8___imgs_|   v							|_0,64_32,64_64,64_|    v
		imgs on a sheet									img pos on sheet
	*/
	this->lines = 0;
	// Check all lines in the sprite sheet
	for (int j = 0; j < this->height; j += sprite_height)
	{
		this->columns = 0;
		// Check all columns in the sprite sheet
		for (int i = 0; i < this->width; i += sprite_width)
		{
			// Get Clip for Sprite in the current position
			SDL_Rect* clip = new SDL_Rect();
			clip->x = i;
			clip->y = j;
			clip->w = sprite_width;
			clip->h = sprite_height;
			//clip = {i, j, sprite_width, sprite_height};
			spriteClips.push_back(clip);

			this->columns++;
		}
		this->lines++;
	}
	// Get how many Sprites we have in the Sprite Sheet (include empty spaces)
	this->size = spriteClips.size();
	//printf("DEBUG: Spritesheet %ix%i size: %i\n", lines, columns, size);
	return true;
}
// Load Sprite Sheets using a XML metadata for the Sprites
// Supports: MuSSEXmlParser.
bool SpriteSheet::create(std::string path, std::string musse_xml_path)
{
	// Open the parser
	MuSSEXmlParser parsed_xml;
	if(!parsed_xml.parseXmlFile(musse_xml_path.c_str())) return false;

	// Create a Sprite with specified image path
	if (!initImage(path/*parsed_xml.getPath(), parsed_xml.getColorKey()*/)) return false;

	// Get the clips
	this->spriteClipsFromXml = parsed_xml.getClips();
	for (std::pair<std::string, SDL_Rect*> s : spriteClipsFromXml) spriteClips.push_back(s.second);

	this->size = spriteClipsFromXml.size();

	// Couldn't read animations
	if (this->size <= 0) {
		printf("ERROR: Couldn't get clips for Animations from XML.\n");
		return false;
	}

	//printf("DEBUG: Spritesheet %s size: %i\n", parsed_xml.getName().c_str(), size);
	return true;
}

/*
*		    *************************************
*					    Getting Sprites
*			*************************************
*/

/*
	Get a sprite (or clip) at a particular cell on the sprite sheet

	int sheetPosX - the X position of the cell on the SpriteSheet
	int sheetPosY - the Y position of the cell on the SpriteSheet

	sheet pos X --->
	_____________________
	| 0,0  1,0  2,0  3,0 |   |					0  1  2  3
	| 0,1  1,1	2,1  3,1 |	 | sheet pos Y		4  5  6	 7
	|_0,2__1,2__2,2__3,2_|   v				    8  9  10 11
	imgs on a sheet								sheet ordered count
*/
SDL_Rect* SpriteSheet::getClip(int sheetPosX, int sheetPosY)
{
	int count = getSpriteCountByPos(sheetPosX, sheetPosY);
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("ERROR: Invalid sprite frame position %i \n", count);
		return spriteClips[0];
	}
	//printf("DEBUG: Pos X: %d Pos Y: %d Width: %d Height: %d \n", spriteClips[count]->x, spriteClips[count]->y, spriteClips[count]->w, spriteClips[count]->h);
	return spriteClips[count];
}
SDL_Rect* SpriteSheet::getClip(int count)
{
	if (count < 0 || (unsigned)count > spriteClips.size() - 1) {
		printf("ERROR: Invalid sprite frame position %i \n", count);
		return spriteClips[0];
	}
	//printf("DEBUG: Pos X: %d Pos Y: %d Width: %d Height: %d \n", spriteClips[count]->x, spriteClips[count]->y, spriteClips[count]->w, spriteClips[count]->h);
	return spriteClips[count];
}
vector<SDL_Rect*> SpriteSheet::getClip(std::string name)
{
	vector<SDL_Rect*> novo;

	for (pair<std::string, SDL_Rect*> s : spriteClipsFromXml)
	{
		if (s.first == name){
			novo.push_back(s.second);
		}
	}

	//printf("DEBUG: Clips for Animation %s returned. Frames Quantity: %d \n", name.c_str(), novo.size());
	return novo;
}
bool SpriteSheet::clipExist(std::string name)
{
	// Check if Sprite Sheet has been read from Xml
	if (spriteClipsFromXml.size() <= 0) {
		printf("ERROR: Sprite Sheet ain't loaded from Xml or error occurred while loading animations.\n");
		return false;
	}

	// Check if theres a animation with that name
	bool hasAnim = false;
	for (pair<std::string, SDL_Rect*> s : spriteClipsFromXml)
	{
		if (s.first == name){
			hasAnim = true;
			break;
		}
	}
	if (!hasAnim) {
		printf("ERROR: There is no Animation with name %s.\n", name.c_str());
		return false;
	}
	
	return true;
}

int SpriteSheet::getSpriteCountByPos(int sheetPosX, int sheetPosY) { return sheetPosX + (sheetPosY * columns); }

int SpriteSheet::getSpriteCount() {	return this->size; }
int SpriteSheet::getHorizontalCount() {	return this->lines; }
int SpriteSheet::getVerticalCount() { return this->columns; }

int SpriteSheet::getWidth() { return width; }
int SpriteSheet::getHeight() { return height; }
SDL_Texture* SpriteSheet::getImage() { return image; }


bool SpriteSheet::initImage(std::string path, Color* transparent)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("ERROR: Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			printf("ERROR: Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(Graphics::renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				printf("ERROR: Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &pixels, &pitch);

				//Copy loaded/formatted surface pixels
				memcpy(pixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				width = formattedSurface->w;
				height = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixs = (Uint32*)pixels;
				int pixelCount = (pitch / 4) * height;

				//Map colors
				SDL_Color colorTransparency = ColorManager::getColor(transparent);
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, colorTransparency.r, colorTransparency.g, colorTransparency.b);
				Uint32 transparency = SDL_MapRGBA(formattedSurface->format, 0x00, 0xFF, 0xFF, 0x00);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixs[i] == colorKey)
					{
						pixs[i] = transparency;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				pixels = NULL;
			}

			//Get rid of old formatted surface
			SDL_FreeSurface(formattedSurface);
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	//printf("DEBUG: Sucessfully loaded image: %s\n", path.c_str());
	image = newTexture;
	return image != NULL;
}