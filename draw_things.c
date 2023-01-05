#include "maze.h"

void draw(SDL_Instance instance, char **map, double_s play,
		  double_s dir, double_s plane)
{
	draw_background(instance);
	draw_walls(map, play, instance, dir, plane);
	SDL_RenderPresent(instance.renderer);
}

void draw_background(SDL_Instance instance)
{
	size_t x;

	for (x = 0; x <= SCREEN_WIDTH; x++)
	{
		SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0x88, 0xFF);
		SDL_RenderDrawLine(instance.renderer, x, 0, x, SCREEN_HEIGHT / 2);
		SDL_SetRenderDrawColor(instance.renderer, 0x88, 0x88, 0x88, 0xFF);
		SDL_RenderDrawLine(instance.renderer, x, SCREEN_HEIGHT / 2,
						   x, SCREEN_HEIGHT);
	}
}


void draw_walls(char **map, double_s play, SDL_Instance instance,
				double_s dir, double_s plane)
{
	double_s ray_pos, ray_dir, dist_side, dist_del;
	double wall_dist, cam_x;
	int_s coord, step;
	int wall_height, wall_start, wall_end, screen_x, hit_side;

	for (screen_x = 0; screen_x < SCREEN_WIDTH; screen_x++)
	{
		hit_side = 0;
		cam_x = 2 * screen_x / (double)SCREEN_WIDTH - 1;
		ray_pos.x = play.x;
		ray_pos.y = play.y;
		ray_dir.x = dir.x + plane.x * cam_x;
		ray_dir.y = dir.y + plane.y * cam_x;
		coord.x = (int)ray_pos.x;
		coord.y = (int)ray_pos.y;
		dist_del.x = sqrt(1 + (ray_dir.y * ray_dir.y) / (ray_dir.x * ray_dir.x));
		dist_del.y = sqrt(1 + (ray_dir.x * ray_dir.x) / (ray_dir.y * ray_dir.y));
		check_ray_dir(&step, &dist_side, ray_pos, coord, dist_del, ray_dir);
		wall_dist = get_wall_dist(map, &dist_side, &coord, &step,
								  &dist_del, &hit_side, &ray_dir, &ray_pos);
		wall_height = (int)(SCREEN_HEIGHT / wall_dist);
		wall_start = -wall_height / 2 + SCREEN_HEIGHT / 2;
		if (wall_start < 0)
			wall_start = 0;
		wall_end = wall_height / 2 + SCREEN_HEIGHT / 2;
		if (wall_end >= SCREEN_HEIGHT)
			wall_end = SCREEN_HEIGHT - 1;
		choose_color(instance, map, coord, hit_side);
		SDL_RenderDrawLine(instance.renderer, screen_x, wall_start,
				   screen_x, wall_end);
	}
}


void choose_color(SDL_Instance instance, char **map, int_s coord, int hit_side)
{
		switch (map[coord.x][coord.y])
		{
		case '1':
			/* Dark Green walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x55, 0x6B, 0x2F, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x80, 0x80, 0, 0xFF);
			break;
		case '2':
			/* Dark Yellow Walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0xCC, 0xCC, 0, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x66, 0x66, 0, 0xFF);
			break;
		case '3':
			/* Red Brick color Walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0xB7, 0x32, 0x39, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x92, 0x28, 0x2E, 0xFF);
			break;
		case '4':
			/* Brown Walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0x7B, 0x3F, 0, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0x5C, 0x40, 0x33, 0xFF);
			break;
		default:
			/* White Walls */
			if (hit_side == 0)
				SDL_SetRenderDrawColor(instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			else
				SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 0xFF);
			break;
		}
}
