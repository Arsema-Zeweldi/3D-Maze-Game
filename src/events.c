#include "../headers/Game.h"

/**
* poll_events - getting quit event
* Return: void.
*/
int poll_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				p.walkDirection = +1;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				p.turnDirection = -1;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				p.turnDirection = +1;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				p.walkDirection = -1;
				break;
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				p.walkDirection = 0;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				p.turnDirection = 0;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				p.turnDirection = 0;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				p.walkDirection = 0;
				break;
			default:
				break;

			}
			break;
		
		}
	}
	return (0);
}
