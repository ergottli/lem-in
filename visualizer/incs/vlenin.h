#ifndef VLENIN_H
# define VLENIN_H

# include "v_lem_in.h"
# include "SDL.h"
# include "SDL_image.h"

# define MAX_SHIPS 1000
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 1000
# define MARGIN 200
# define MAP_WIDTH (WINDOW_WIDTH - MARGIN)
# define MAP_HEIGHT (WINDOW_HEIGHT - MARGIN)
# define RELATIVE_DIVISION_RATIO 100

typedef struct		s_viz
{
	SDL_Event		event;
	SDL_Window		*gwindow;
	SDL_Renderer	*grenderer;
	SDL_Texture		*texture_background;
	t_point			min;
	t_point			max;
	SDL_Surface		*planet_red;
	SDL_Texture		*planet_red_texture;
	SDL_Surface		*planet_blue;
	SDL_Texture		*planet_blue_texture;
	SDL_Surface		*planet_grey;
	SDL_Texture		*planet_grey_texture;
	SDL_Surface		*star;
	SDL_Surface		*black_hole;
	SDL_Texture		*black_hole_texture;
	SDL_Surface		*ship;
	SDL_Texture		*ship_texture;
	SDL_Surface		*space;
	SDL_Texture		*star_texture;
	SDL_Rect		ships[MAX_SHIPS];
	t_point			destination[MAX_SHIPS];
	t_point			current[MAX_SHIPS];
	t_point			distance[MAX_SHIPS];
	t_point			offset[MAX_SHIPS];
	int				angle[MAX_SHIPS];
	int				sh_in_move[MAX_SHIPS];
	void			*nullptr;
	int				success;
	int				quit;
	int				frame;
	int				cap;
	int				started;
	int				paused;
	double			tasmanian;
}					t_viz;

int					ft_next_parse(t_graph *g);
int					init();
int					create_window(int sc_width, int sc_height);
SDL_Texture			*create_texture_frome_surface(char *path);
SDL_Surface			*loadsurface(char *path);
int					load_media();
void				close_window();
int					mainframe(t_graph *g);
int					catch_events(SDL_Event event);
void				apxs_coord_rel_to_abs(t_graph *g);
void				apxs_coords_rw_to_rel(t_graph *g, t_viz *vi);
void				coords_stabilize(t_graph *g);
void				find_minmax_coords(t_graph *g, t_viz *vi);
t_point				brasenham(t_point current, t_point destination, int ship);
int					graph_draw(t_graph *g);
void				graph_draw_start_end(t_graph *g, int i);
void				path_draw(t_graph *g);
t_viz				*g_vi;

#endif
