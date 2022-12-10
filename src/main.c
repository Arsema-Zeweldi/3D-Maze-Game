#include "../headers/Game.h"

/*
#define COLS 15
#define ROWS 15
#define NUM_RAYS xpos
*/
/* Declaration of Global Variables */



const int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1},
	{1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 3, 0, 1, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


struct Player p;
struct Ray rays[NUM_RAYS];
int ticksLastFrame;
uint32_t *colorBuffer = NULL;
SDL_Texture *colorBufferTexture;
Uint32 *wallTexture = NULL;
Uint32 *textures[NUM_TEXTURES];
//SDL_Rect src, dest;

/**
 * main - main work
 * Return: always 0.
 */
int main(void)
{
	Game instance;

	/* Initializing the Window and Render */
	if (init_instance(&instance) != 0)
		return (1);

	setupPlayer(instance);

	while (isRunning)
	{
		SDL_RenderClear(instance.renderer);
		if (poll_events() == 1)
			break;
		/* update */
		update();
		SDL_SetRenderDrawColor(instance.renderer, 255, 0, 255, 255);
		SDL_RenderClear(instance.renderer);
		/* create 3D */
		generate3DProjection();

		/* color */
		renderColorBuffer(instance);
		clearColorBuffer(0xFF000000);

		/* render game */
		renderMap(instance);
		renderRays(instance);
		renderPlayer(instance);
		SDL_RenderPresent(instance.renderer);
	}
	free(wallTexture);
	free(colorBuffer);
	/*
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	*/
	clean(instance);

	return (0);
}

/*
void updateMap(Game instance)
{
	bottom = LoadTexture(instance.renderer, "cobble.png");
	wall = LoadTexture(instance.renderer, "bush.png");
	win = LoadTexture(instance.renderer, "win.png");
	bigfoot = LoadTexture(instance.renderer, "bigfoot.png");

	//LoadMap(level1);

	src.x = 0;
	src.y = 0;
	src.w = 32;
	src.h = 32;

	dest.x = 0;
	dest.y = 0;
	dest.w = 32;
	dest.h = 32;
}
*/
/*
void LoadMap(int arr[ROWS][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			map[i][j] = arr[i][j];
		}
	}
}
*/
/*
void DrawMap(Game instance)
{
	int type = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			type = map[i][j];

			dest.x = j * 32;
			dest.y = i * 32;

			switch (type)
			{
			case 0:
				SDL_RenderCopy(instance.renderer, bottom, &src, &dest);
				break;
			case 1:
				SDL_RenderCopy(instance.renderer, wall, &src, &dest);
				break;
			case 2:
				SDL_RenderCopy(instance.renderer, win, &src, &dest);
				break;
			case 3:
				SDL_RenderCopy(instance.renderer, bottom, &src, &dest);
				break;
			default:
				break;
			}
		}
	}
}
*/
