#include "../headers/Game.h"


/**
 * normalizeAngle - normalizing the angle
 * @angle: the angle
 * Return: the normal angle
 */
float normalizeAngle(float angle)
{
    angle = remainder(angle, (M_PI * 2));
    if (angle < 0)
        angle = (M_PI * 2) + angle;
    return (angle);
}

/**
 * distanceBetweenPoints - measures distance between points
 * @x1: first x point
 * @y1: first y point
 * @x2: second x point
 * @y2: second y point
 * Return: the distance
 */
float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * castAllRays - casts the rays
 * Return: void
 */

/**
 * castRay - casts rays
 * @rayAngle: the ray angle
 * @stripId: counter
 */
void castRay(float rayAngle, int stripId)
{
	rayAngle = normalizeAngle(rayAngle);

	int isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	int isRayFacingUp = !isRayFacingDown;

	int isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	int isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	/* Horizontal ray-grid intersection code */
	int foundHorzWallHit = FALSE;
	float horzWallHitX = 0;
	float horzWallHitY = 0;
	int horzWallContent = 0;

	/* Finding the y-coordinate of the closest horizontal grid intersection */
	yintercept = floor(p.y / SIZE) * SIZE;
	yintercept += isRayFacingDown ? SIZE : 0;

	/* Finding the x-coordinate of the closest horizontal grid intersection */
	xintercept = p.x + (yintercept - p.y) / tan(rayAngle);

	/* Calculate the increment xstep and ystep */
	ystep = SIZE;
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;

	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	/* Incrementing xstep and ystep until finding a wall */
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= xpos &&
			nextHorzTouchY >= 0 && nextHorzTouchY <= ypos)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			/* found a wall hit */
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(yToCheck / SIZE)]
									[(int)floor(xToCheck / SIZE)];
			foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	}
	int foundVertWallHit = FALSE;
	float vertWallHitX = 0;
	float vertWallHitY = 0;
	int vertWallContent = 0;

	xintercept = floor(p.x / SIZE) * SIZE;
	xintercept += isRayFacingRight ? SIZE : 0;
	yintercept = p.y + (xintercept - p.x) * tan(rayAngle);
	xstep = SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;

	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	while (nextVertTouchX >= 0 && nextVertTouchX <= xpos &&
			nextVertTouchY >= 0 && nextVertTouchY <= ypos)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map[(int)floor(yToCheck / SIZE)]
									[(int)floor(xToCheck / SIZE)];
			foundVertWallHit = TRUE;
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	float horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(p.x, p.y, horzWallHitX, horzWallHitY)
		: INT_MAX;
	float vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(p.x, p.y, vertWallHitX, vertWallHitY)
		: INT_MAX;
	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wallHitContent = vertWallContent;
		rays[stripId].wasHitVertical = TRUE;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wallHitContent = horzWallContent;
		rays[stripId].wasHitVertical = FALSE;
	}
	rays[stripId].rayAngle = rayAngle;
	rays[stripId].isRayFacingDown = isRayFacingDown;
	rays[stripId].isRayFacingUp = isRayFacingUp;
	rays[stripId].isRayFacingLeft = isRayFacingLeft;
	rays[stripId].isRayFacingRight = isRayFacingRight;
}

/**
 * castAllRays - casts the rays
 * Return: void
 */
void castAllRays(void)
{
    int stripld;
    float rayAngle;

    rayAngle = p.rotationAngle - (FOV_ANGLE / 2);

    for (stripld = 0; stripld < NUM_RAYS; stripld++)
    {
        castRay(rayAngle, stripld);
        rayAngle += FOV_ANGLE / NUM_RAYS;
    }
}

/**
 * renderMap - rendering the map
 * @instance: Game instance
 * Return: void
 */
void renderMap(Game instance)
{
	bottom = LoadTexture(instance.renderer, "cobble.png");
	wall = LoadTexture(instance.renderer, "bush.png");
	win = LoadTexture(instance.renderer, "win.png");
	bigfoot = LoadTexture(instance.renderer, "bigfoot-new.png");

    int i, j, tileX, tileY, tileColor;
	int type = 0;

    for (i = 0; i < COLS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            tileX = j * SIZE;
            tileY = i * SIZE;
            tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

            SDL_SetRenderDrawColor(instance.renderer, tileColor,
                                tileColor, tileColor, 255);

            SDL_Rect mapTileRect = {
                tileX * MINIMAP_SCALE_FACTOR,
                tileY * MINIMAP_SCALE_FACTOR,
                SIZE * MINIMAP_SCALE_FACTOR,
                SIZE * MINIMAP_SCALE_FACTOR,
            };

			switch (type)
			{
			case 0:
				SDL_RenderCopy(instance.renderer, bottom, NULL, &mapTileRect);
				break;
			case 1:
				SDL_RenderCopy(instance.renderer, wall, NULL, &mapTileRect);
				break;
			case 2:
				SDL_RenderCopy(instance.renderer, win, NULL, &mapTileRect);
				break;
			case 3:
				SDL_RenderCopy(instance.renderer, bigfoot, NULL, &mapTileRect);
				break;
			default:
				break;
			}
            SDL_RenderFillRect(instance.renderer, &mapTileRect);
        }
    }
}

/**
 * renderRays - renders rays
 * @instance: Game instance
 * Return: void
 */
void renderRays(Game instance)
{
    int i;

    SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
    for (i = 0; i < NUM_RAYS; i++)
    {
        SDL_RenderDrawLine(
            instance.renderer,
            MINIMAP_SCALE_FACTOR * p.x,
            MINIMAP_SCALE_FACTOR * p.y,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitX,
            MINIMAP_SCALE_FACTOR * rays[i].wallHitY
        );
    }
}
