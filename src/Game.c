#include "../headers/Game.h"

SDL_Rect drect;
SDL_Texture *playerTex;
SDL_Surface *tmpSurface;

/**
* init_instance - initializing SDL2
* @instance: new instance
* Return: 0 if it fails, 1 if it's successful.
*/
int init_instance(Game *instance)
{
	/* Initializing SDL */
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		printf("SDL Initialized\n");

		/* Creating a new Window instance */
		instance->window = SDL_CreateWindow("Maze", SDL_WINDOWPOS_CENTERED,
							SDL_WINDOWPOS_CENTERED,
							xpos, ypos, SDL_WINDOW_RESIZABLE);
		if (instance->window)
		{
			printf("Window successfully created\n");
		}
		
		/* Create a new Renderer instance linked to the Window */
		instance->renderer = SDL_CreateRenderer(instance->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
		if (instance->renderer)
		{
			SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);
			printf("Renderer successfully created\n");
		}

		isRunning = true;
	}
	else
	{
		//printf("NOt working");
		isRunning = false;
	}

	//playerTex = LoadTexture(instance->renderer, "player.png");

	return (0);
}
/*
void rect()
{
	drect.h = 100;
	drect.w = 320;
	drect.x = 250;
	drect.y = 500;
}
*/

void renderPlayer(Game instance)
{
	//SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);

	SDL_Rect playerRect = {
		p.x * MINIMAP_SCALE_FACTOR,
		p.y * MINIMAP_SCALE_FACTOR,
		p.width * MINIMAP_SCALE_FACTOR,
		p.height * MINIMAP_SCALE_FACTOR
	};
	
	drect.h = 250;
	drect.w = 500;
	drect.x = 450;
	drect.y = 450;

	SDL_Surface *tmpSurface = IMG_Load("myPlayer.png");
	SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGBA(tmpSurface->format,
			255, 0, 255, 255));
	SDL_Texture *playerTex = SDL_CreateTextureFromSurface(instance.renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	/*
	playerTex = LoadTexture(instance.renderer, "player.bmp");
	*/
	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
	SDL_RenderCopy(instance.renderer, playerTex, NULL, &drect);
	SDL_RenderFillRect(instance.renderer, &playerRect);
	//SDL_RenderPresent(instance.renderer);

	SDL_RenderDrawLine(
		instance.renderer,
		MINIMAP_SCALE_FACTOR * p.x,
		MINIMAP_SCALE_FACTOR * p.y,
		MINIMAP_SCALE_FACTOR * (p.x + cos(p.rotationAngle) * 40),
		MINIMAP_SCALE_FACTOR * (p.y + sin(p.rotationAngle) * 40)
	);
}

/*
void render(Game instance)
{
	SDL_RenderClear(instance.renderer);
	SDL_RenderCopy(instance.renderer, playerTex, NULL, &playerRect);
	SDL_RenderPresent(instance.renderer);
}
*/
void clean(Game instance)
{
	SDL_DestroyWindow(instance.window);
	SDL_DestroyRenderer(instance.renderer);
	SDL_Quit();
	printf("Game cleaned\n");
}
