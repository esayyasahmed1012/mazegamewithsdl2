#ifndef MAZE_H
#define MAZE_H


#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define SCREEN_HEIGHT 768
#define SCREEN_WIDTH 1024
#define MAP_WIDTH 24
#define MAP_HEIGHT 24


typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

typedef struct double_s
{
	double x;
	double y;
} double_s;


typedef struct int_s
{
	int x;
	int y;
} int_s;


typedef struct keys
{
	int up;
	int down;
	int right;
	int left;
} keys;


typedef struct level
{
	char **map;
	size_t height;
	int_s win;
	double_s play;
	double_s dir;
	double_s plane;
} level;


int init_instance(SDL_Instance *);

int keyboard_events(keys *);
void check_key_release_events(SDL_Event, keys *);
int check_key_press_events(SDL_Event, keys *);


char **create_map(char *, double_s *, int_s *, size_t *);
void plot_grid_points(char **, double_s *, int_s *, size_t, size_t, char *,
		      int *);
size_t get_line_count(char *);
size_t get_char_count(char *);

level *build_world_from_args(int, char **);

void draw(SDL_Instance, char **, double_s, double_s, double_s);
void draw_walls(char **, double_s, SDL_Instance, double_s, double_s);
void choose_color(SDL_Instance, char **, int_s, int);
void draw_background(SDL_Instance);


void rotate(double_s *, double_s *, int);
void movement(keys, double_s *, double_s *, double_s *, char **);


void print_win(void);
int check_win(double_s, int_s, int *);


double get_wall_dist(char **, double_s *, int_s *, int_s *, double_s *, int *,
		     double_s *, double_s *);
void check_ray_dir(int_s *, double_s *, double_s, int_s, double_s, double_s);


void free_memory(SDL_Instance, char **, size_t);
void free_map(char **, size_t);
void close_SDL(SDL_Instance);

#endif
