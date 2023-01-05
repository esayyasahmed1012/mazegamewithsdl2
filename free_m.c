#include "maze.h"

void free_memory(SDL_Instance instance, char **map, size_t map_h)
{
	free_map(map, map_h);
	close_SDL(instance);
}

void free_map(char **map, size_t map_h)
{
	size_t i = 0;

	while (i < map_h)
	{
		free(map[i]);
		i++;
	}
}

void close_SDL(SDL_Instance instance)
{
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
}
