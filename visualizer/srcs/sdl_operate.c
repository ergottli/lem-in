#include "vlenin.h"

void		close_window(void)
{
	SDL_FreeSurface(g_vi->space);
	SDL_FreeSurface(g_vi->ship);
	SDL_FreeSurface(g_vi->star);
	SDL_FreeSurface(g_vi->planet_red);
	SDL_FreeSurface(g_vi->planet_grey);
	SDL_FreeSurface(g_vi->planet_blue);
	SDL_FreeSurface(g_vi->black_hole);
	g_vi->space = NULL;
	g_vi->ship = NULL;
	g_vi->star = NULL;
	g_vi->planet_grey = NULL;
	g_vi->planet_red = NULL;
	g_vi->planet_blue = NULL;
	g_vi->black_hole = NULL;
	SDL_DestroyRenderer(g_vi->grenderer);
	SDL_DestroyWindow(g_vi->gwindow);
	g_vi->gwindow = NULL;
	g_vi->grenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	exit(0);
}

int			catch_events(SDL_Event event)
{
	int quit;

	quit = 0;
	while (SDL_PollEvent(&event))
		if (event.type == SDL_QUIT)
			quit = 1;
	return (quit);
}

SDL_Surface	*loadsurface(char *path)
{
	SDL_Surface *loadedsurface;

	if (!(loadedsurface = IMG_Load(path)))
	{
		ft_printf(ANSI_B_RED"Unable to load image %s! "
		"SDL_image Error: %s\n"ANSI_RESET, path, IMG_GetError());
		return (NULL);
	}
	return (loadedsurface);
}

SDL_Texture	*create_texture_frome_surface(char *path)
{
	SDL_Surface *surface;
	SDL_Texture *texture;

	if (!(surface = loadsurface(path)))
	{
		ft_printf(ANSI_B_RED"loadsurface filed\n"ANSI_RESET);
		close_window();
	}
	if (!(texture = SDL_CreateTextureFromSurface(g_vi->grenderer, surface)))
	{
		ft_printf(ANSI_B_RED "SDL_CreateTextureFromSurface failed! "
		"SDL_CreateTextureFromSurface Error: %s\n" ANSI_RESET, IMG_GetError());
		close_window();
	}
	if ((SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) < 0))
	{
		ft_printf(ANSI_B_RED"SDL_SetTextureBlendModefailed! "
			"SDL_SetTextureBlendMode Error: %s\n"ANSI_RESET, IMG_GetError());
		close_window();
	}
	SDL_FreeSurface(surface);
	return (texture);
}

int			create_window(int sc_width, int sc_height)
{
	g_vi->gwindow = SDL_CreateWindow("LEM-IN Visualizer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		sc_width, sc_height, SDL_WINDOW_SHOWN);
	if (!g_vi->gwindow)
	{
		ft_printf("viz->window could not "
			"be created! SDL_Error: %s\n", SDL_GetError());
		return (g_vi->success = 0);
	}
	g_vi->grenderer = SDL_CreateRenderer(g_vi->gwindow,
			-1, SDL_RENDERER_ACCELERATED);
	if (!g_vi->grenderer)
	{
		ft_printf(ANSI_B_RED"Renderer "
					"could not be created! SDL Error: %s\n", SDL_GetError());
		return (g_vi->success = 0);
	}
	SDL_SetRenderDrawColor(g_vi->grenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	return (g_vi->success);
}
