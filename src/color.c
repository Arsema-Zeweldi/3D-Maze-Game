#include "../headers/Game.h"

/**
 * clearColorBuffer - clears the color buffer
 * @color: the color
 * Return: void
 */
void clearColorBuffer(Uint32 color)
{
	for (int x = 0; x < xpos; x++)
	{
		for (int y = 0; y < ypos; y++)
			colorBuffer[(xpos * y) + x] = color;
	}
}

/**
 * renderColorBuffer - renders the color buffer
 * @instance: Game instance
 * Return: void
 */
void renderColorBuffer(Game instance)
{
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)((Uint32)xpos * sizeof(Uint32))
	);
	SDL_RenderCopy(instance.renderer, colorBufferTexture, NULL, NULL);
}
