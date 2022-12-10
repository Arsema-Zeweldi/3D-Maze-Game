#ifndef GAME_h
#define GAME_h

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "texture.h"
#include "global.h"

bool isRunning;
//typedef uint32_t color_t;

typedef struct Game
{

	SDL_Window *window;
	SDL_Renderer *renderer;
} Game;

typedef struct Double
{
	double x;
	double y;
} Double;

typedef struct Int
{
	int i;
	int j;
} Int;

/*
typedef struct level
{
	char **map;
} level;
*/

const int map[ROWS][COLS];
/*int isRunning;*/
extern SDL_Window *window;
extern SDL_Renderer *renderer;

struct Player
{
	float x;
	float y;
	float width;
	float height;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
};

struct Player p;

struct Ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int isRayFacingUp;
	int isRayFacingDown;
	int isRayFacingRight;
	int isRayFacingLeft;
	int wallHitContent;
} rays[NUM_RAYS];

extern struct Ray rays[NUM_RAYS];
int ticksLastFrame;
Uint32 *colorBuffer;
SDL_Texture *colorBufferTexture;
Uint32 *wallTexture;
Uint32 *textures[NUM_TEXTURES];


/* Events.c */
//int handleEvents(void);
//void update(void);
//void render(Game instance);
//void clean(Game instance);

/* Time.c */
void update(void);
//void clean(Game instance);

/* Game.c */
int init_instance(Game *instance);
void renderPlayer(Game instance);
void clean(Game instance);

/* Events.c */
int poll_events(void);
int poll_events_keyUp(void);

/* Player.c */
void setupPlayer(Game instance);
void movePlayer(float deltaTime);
int mapHasWallAt(float x, float y);

/* Render.c */
void renderMap(Game instance);
void castAllRays(void);
void castRay(float rayAngle, int stripId);
float normalizeAngle(float angle);
float distanceBetweenPoints(float x1, float y1, float x2, float y2);
void renderRays(Game instance);

/* Color.c */
void clearColorBuffer(Uint32 color);
void renderColorBuffer(Game instance);

/* 3D */
void generate3DProjection(void);

//void win(void);
//int check_win(Double, Int, int *);

/*
void rect();
void LoadMap(int arr[ROWS][COLS]);
void DrawMap(Game instance);
void updateMap(Game instance);
*/

SDL_Rect src, dest;


SDL_Texture *bottom;
SDL_Texture *wall;
SDL_Texture *win;
SDL_Texture *bigfoot;

//SDL_Texture *textures[NUM_TEXTURES];

SDL_Texture *LoadTexture(SDL_Renderer *ren, const char *fileName);
void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest);

#endif /* Game_h */
