#include "vlenin.h"

int		load_media(void)
{
	int	img_flags;

	img_flags = IMG_INIT_PNG;
	ft_printf("start media loaded\n");
	if (!(IMG_Init(img_flags) & img_flags))
	{
		ft_printf(ANSI_B_RED"SDL_image could not initialize!"
		"SDL_image Error: %s\n"ANSI_RESET, IMG_GetError());
		g_vi->success = 0;
	}
	g_vi->texture_background =
			create_texture_frome_surface("./img/space.png");
	g_vi->planet_red_texture =
			create_texture_frome_surface("./img/planet-pink-blue.png");
	g_vi->planet_grey_texture =
			create_texture_frome_surface("./img/planet-grey.png");
	g_vi->planet_blue_texture =
			create_texture_frome_surface("./img/planet-blue.png");
	g_vi->star_texture = create_texture_frome_surface("./img/star.png");
	g_vi->black_hole_texture =
			create_texture_frome_surface("./img/black-hole.png");
	g_vi->ship = loadsurface("./img/jm.png");
	g_vi->ship_texture =
			create_texture_frome_surface("./img/plankton.png");
	return (g_vi->success);
}

t_viz	*init_values(void)
{
	int i;

	i = -1;
	if (!(g_vi = (t_viz*)ft_memalloc(sizeof(t_viz))))
		return (NULL);
	g_vi->frame = 0;
	g_vi->gwindow = NULL;
	g_vi->planet_blue_texture = NULL;
	g_vi->planet_red_texture = NULL;
	g_vi->planet_grey_texture = NULL;
	g_vi->star_texture = NULL;
	g_vi->black_hole_texture = NULL;
	g_vi->ship = NULL;
	g_vi->grenderer = NULL;
	g_vi->success = 1;
	g_vi->quit = 0;
	ft_bzero(g_vi->sh_in_move, MAX_SHIPS);
	while (++i < MAX_SHIPS)
	{
		g_vi->current[i].x = INT32_MIN;
		g_vi->current[i].y = INT32_MIN;
	}
	return (g_vi);
}

int		init(void)
{
	g_vi = init_values();
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf(ANSI_B_RED"SDL could not initialize! "
			"SDL Error: %s\n"ANSI_RESET, SDL_GetError());
		g_vi->success = 0;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
			ft_printf("Warning: Linear texture filtering not enabled!");
		ft_printf("texture filtering on\n");
		if (!create_window(WINDOW_WIDTH, WINDOW_HEIGHT))
			return (g_vi->success = 0);
		load_media();
	}
	return (g_vi->success);
}
