#ifndef GLOBAL_h
#define GLOBAL_h

#include <math.h>

#define FALSE 0
#define TRUE 1

//#define PI 3.14159265
//#define TWO_PI 6.28318530

#define SIZE 80
#define ROWS 15
#define COLS 15
#define NUM_TEXTURES 1

#define MINIMAP_SCALE_FACTOR 0.10

#define xpos (COLS * SIZE)
#define ypos (ROWS * SIZE)

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define NUM_RAYS xpos

#define FOV_ANGLE (60 * (M_PI / 180))

#define FPS 60
#define FRAME_TIME_LENGTH (1000 / FPS)

#endif // !GLOBAL_h

