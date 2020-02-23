// Includes
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdbool.h>

#include <graphics/graphics.h>
#include <graphics/framebuffer.h>
#include <graphics/renderer_map.h>
#include <io/error.h>
#include <io/map.h>
#include <graphics/renderer_fp.h>
#include <game/player.h>

#define MOVEMENT_SPEED	10

FRAMEBUFFER_HANDLE *	fb;

int main
(
	int argc,
	char* argv[]
)
{
	MAP map;
	bool draw = true;
	RENDERER_POINT a = { 0, 0 };
	RENDERER_POINT b = { 300, 0 };
	RENDERER_POINT c = { 300, 300 };
	RENDERER_POINT d = { 200, 50 };
	RENDERER_POINT pts[] = { a, b, c, d };
	RENDERER_POLYGON polygon =
	{
		4,
		pts
	};

	Error_Handle(Map_Load(argv[1], &map));

	Error_Handle(Framebuffer_Create(&fb));

	player.height = PLAYER_HEIGHT;
	player.position.x = 50;
	player.position.y = 50;
	

	while (draw)
	{
		SDL_Event event;

		Renderer_FirstPerson_Render(fb, &map);
		Graphics_DrawMap(fb, &map);
		Framebuffer_Blit(fb);
		Framebuffer_Clear(fb, 0xFF000000);

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				draw = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_w)
				{
					player.position.x += (Angle_Cos(player.angle) * MOVEMENT_SPEED);
					player.position.y -= (Angle_Sin(player.angle) * MOVEMENT_SPEED);
				}
				if (event.key.keysym.sym == SDLK_s)
				{
					player.position.x += (Angle_Cos(player.angle) * -MOVEMENT_SPEED);
					player.position.y -= (Angle_Sin(player.angle) * -MOVEMENT_SPEED);
				}
				if (event.key.keysym.sym == SDLK_a)
				{
					player.position.x += (Angle_Cos(player.angle + 90.0) * MOVEMENT_SPEED);
					player.position.y -= (Angle_Sin(player.angle + 90.0) * MOVEMENT_SPEED);
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					player.position.x += (Angle_Cos(player.angle - 90.0) * MOVEMENT_SPEED);
					player.position.y -= (Angle_Sin(player.angle - 90.0) * MOVEMENT_SPEED);
				}
				if (event.key.keysym.sym == SDLK_q)
				{
					Player_SetAngle(&player, player.angle + 10.0f);
				}
				if (event.key.keysym.sym == SDLK_e)
				{
					Player_SetAngle(&player, player.angle - 10.0f);
				}
				if (event.key.keysym.sym == SDLK_1)
				{
					player.height -= 10;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					player.height += 10;
				}
			}
		}
	}

	Error_Handle(Framebuffer_Destroy(fb));

	return 0;
}