#include <stdio.h>
#include <string.h>
#include "raylib.h"

typedef struct s_grain
{
	Color	color;
	float	dy;
	int		x;
	int		y;
	int		size;
}		t_grain;

#define GRAVITY 1.04
#define DY		5;
#define MAX_GRAINS 10000
int	main(void)
{
	const int	screenWidth = 16*50;
	const int	screenHeight = 10*50;
	int			elevation[screenWidth];

	t_grain	grains[MAX_GRAINS];
	int	grains_count = 0;
	SetTargetFPS(60);
	InitWindow(screenWidth, screenHeight, "sands");
	bzero(elevation, sizeof(elevation));
	while (!WindowShouldClose())
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && grains_count < MAX_GRAINS)
		{
			int	rand = 7 + (grains_count ^ 2346517) % 7;
			int	sign = -1 * rand % 2 + !(rand % 2);
			grains[grains_count].x = GetMouseX() + sign * rand;
			grains[grains_count].y = GetMouseY();
			grains[grains_count].dy = DY;
			grains[grains_count].size = rand / 3;
			grains[grains_count].color.r = 220+rand;
			grains[grains_count].color.g = 200+rand;
			grains[grains_count].color.b = (30 + grains_count) % 255;
			grains[grains_count].color.a = 0xff;
			grains_count++;
		}
		BeginDrawing();
		ClearBackground(BLACK);
		for (int i = 0; i < grains_count; i++)
		{
			t_grain	*grain = &grains[i];
			if (grain->dy && grain->y + elevation[grain->x] > screenHeight)
			{
				grain->y = screenHeight - elevation[grain->x];
				grain->dy = 0;
				for (int i = grain->x; i < grain->x + grain->size; i++)
					elevation[i] += grain->size;
			}
			else
			{
				grain->y += grain->dy;
				grain->dy *= GRAVITY;
			}
			DrawRectangle(grain->x, grain->y, grain->size, grain->size, grain->color);
		}
		EndDrawing();
	}
	CloseWindow();
}
