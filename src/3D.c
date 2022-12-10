#include "../headers/Game.h"


/**
 * generate3DProjection - creating 3d projection
 * Return: Nothing
 */
void generate3DProjection(void)
{
	int k, l, Num_tex, distanceFromTop;
	float perpDistance, distanceProjPlane, projectedWallHeight;
	int wallStripHeight, wallTopPixel, wallBottomPixel;
	int textureOffsetX, textureOffsetY;
	Uint32 texelColor;
	(void)texelColor;

	for (k = 0; k < NUM_RAYS; k++)
	{
		perpDistance = rays[k].distance * cos(rays[k].rayAngle - p.rotationAngle);
		distanceProjPlane = (xpos / 2) / tan(FOV_ANGLE / 2);
		projectedWallHeight = (SIZE / perpDistance) * distanceProjPlane;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (ypos / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		wallBottomPixel = (ypos / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > ypos ? ypos : wallBottomPixel;

		/* roof */
		for (l = 0; l < wallTopPixel; l++)
			colorBuffer[(xpos * l) + k] = 0x9FFCFD;
		
		if (rays[k].wasHitVertical)
			textureOffsetX = (int)rays[k].wallHitY % TEXTURE_HEIGHT;
		else
			textureOffsetX = (int)rays[k].wallHitX % TEXTURE_WIDTH;

		Num_tex = rays[k].wallHitContent - 1;
		
		for (l = wallTopPixel; l < wallBottomPixel; l++)
		{
			distanceFromTop = l + (wallStripHeight / 2) - (ypos / 2);
			textureOffsetY = distanceFromTop * ((float)TEXTURE_HEIGHT
														/ wallStripHeight);
			Uint32 texelColor = textures[Num_tex][(TEXTURE_WIDTH
									* textureOffsetY) + textureOffsetX];
			colorBuffer[(xpos * l) + k] = texelColor;
		}
		/* floor */
		for (l = wallBottomPixel; l < ypos; l++)
			colorBuffer[(xpos * l) + k] = 0x75FA61;
			//colorBuffer[(xpos * l) + k] = bottom;
	}
}
