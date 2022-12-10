#include "../headers/Game.h"

/**
 * setupPlayer - sets characteristics of player
 * @instance: Game instance
 * Return: void
 */
void setupPlayer(Game instance)
{
	p.x = (xpos * 6.2) / 7;
	p.y = (ypos * 6.2) / 7;
	p.width = 10;
	p.height = 10;
	p.turnDirection = 1;
	p.walkDirection = 0;
	p.rotationAngle = M_PI / 2;
	p.walkSpeed = 100;
	p.turnSpeed = 25 * (M_PI / 180);
	/* Allocating the total amount of bytes in memory to hold the colorbuffer */
	colorBuffer = (Uint32 *)malloc(sizeof(Uint32) * (Uint32)xpos * (Uint32)ypos);
	/* Creating an SDL_Texture to display the colorbuffer */
	colorBufferTexture = SDL_CreateTexture(
		instance.renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		xpos,
		ypos
	);
/*
	SDL_Init();
	IMG_Init(IMG_INIT_JPG);
	SDL_Surface *image = SDL_Load("bushes.jpg");
	IMG_Quit();
	SDL_Quit();
*/
	//textures[0] = IMG_LoadTexture(renderer, "bushes.jpg");
	textures[0] = (Uint32 *)WOOD_TEXTURE;
}

/**
* renderPlayer - renders the player
* @instance: sdl instance
* Returns: nothing
*/
/*
void renderPlayer(Game instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
	SDL_Rect playerRect = {
		p.x * MINIMAP_SCALE_FACTOR,
		p.y * MINIMAP_SCALE_FACTOR,
		p.width * MINIMAP_SCALE_FACTOR,
		p.height * MINIMAP_SCALE_FACTOR
	};
	//SDL_RenderCopy(instance.renderer, playerTex, NULL, &playerRect);
	//SDL_RenderFillRect(instance.renderer, &playerRect);

	SDL_RenderDrawLine(
		instance.renderer,
		MINIMAP_SCALE_FACTOR * p.x,
		MINIMAP_SCALE_FACTOR * p.y,
		MINIMAP_SCALE_FACTOR * (p.x + cos(p.rotationAngle) * 40),
		MINIMAP_SCALE_FACTOR * (p.y + sin(p.rotationAngle) * 40)
	);
}
*/

/**
 * mapHasWallAt - detects wall collision
 * @x: position x
 * @y: position y
 * Return: 0 if true, 1 if false
 */
int mapHasWallAt(float x, float y)
{
	int mapGridIndexX, mapGridIndexY;

	if (x < 0 || x > xpos || y < 0 || y > ypos)
		return (0);

	mapGridIndexX = floor(x / SIZE);
	mapGridIndexY = floor(y / SIZE);
	return (map[mapGridIndexY][mapGridIndexX] != 0);
}

/**
 * movePlayer - moving player
 * @deltaTime: time
 * Return: nothing
 */
void movePlayer(float deltaTime)
{
	float moveStep, newPlayerX, newPlayerY;

	p.rotationAngle += p.turnDirection * p.turnSpeed * 1.10 * deltaTime;

	moveStep = p.walkDirection * p.walkSpeed * deltaTime;

	newPlayerX = p.x + cos(p.rotationAngle) * moveStep;
	newPlayerY = p.y + sin(p.rotationAngle) * moveStep;

	if (!mapHasWallAt(newPlayerX, newPlayerY))
	{
		p.x = newPlayerX;
		p.y = newPlayerY;
	}
}


SDL_Texture *LoadTexture(SDL_Renderer *ren, const char *fileName)
{
	SDL_Surface *tmpSurface = IMG_Load(fileName);
	//SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 255, 0, 255));
	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);

	return (tex);
}
