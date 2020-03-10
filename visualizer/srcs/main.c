#include "vlenin.h"

void			ft_graph_init(t_graph *g)
{
	g->apxs = NULL;
	g->dif = NULL;
	g->parents = NULL;
	g->res = NULL;
	g->path_count = 0;
	g->start = -1;
	g->end = -1;
	g->napex = -1;
	g->ant = 0;
	g->ord = 1;
	g->input = 0;
	g->error = 0;
	g->flag = 0;
	g->next_parse = 0;
}

void			ft_graph_del(t_graph *g)
{
	int			i;

	i = -1;
	while (g->apxs[++i])
	{
		if (g->apxs[i]->name != NULL)
			free(g->apxs[i]->name);
		ft_lstdel(&g->apxs[i]->next, ft_content_del);
		free(g->apxs[i]);
	}
	free(g->apxs);
}

void			free_all(t_graph *g)
{
	ft_lstdel(&g->dif, ft_content_del);
	if (g->apxs != NULL)
		ft_graph_del(g);
	if (g->parents != NULL)
		ft_memdel(((void*)&g->parents));
}

int				mainframe(t_graph *g)
{
	SDL_Rect	rect_for_bg;

	if (!init())
		ft_printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	find_minmax_coords(g, g_vi);
	coords_stabilize(g);
	apxs_coords_rw_to_rel(g, g_vi);
	apxs_coord_rel_to_abs(g);
	while (!g_vi->quit)
	{
		g_vi->quit = catch_events(g_vi->event);
		SDL_SetRenderDrawColor(g_vi->grenderer, 0x13, 0x0E, 0x33, 0xFF);
		SDL_RenderClear(g_vi->grenderer);
		rect_for_bg = (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
		SDL_RenderCopy(g_vi->grenderer,
				g_vi->texture_background, NULL, &rect_for_bg);
		path_draw(g);
		close_window();
	}
	ft_printf(ANSI_RED "closing visualizer\n" ANSI_RESET);
	close_window();
	return (0);
}

int				main(void)
{
	t_graph		g;

	ft_graph_init(&g);
	if (!ft_input(&g) && !g.next_parse)
	{
		ft_putendl_fd("error_input", 2);
		free_all(&g);
		return (0);
	}
	if (!ft_inp_com(&g))
	{
		ft_putendl_fd(ANSI_B_GREEN"error_input"ANSI_RESET, 2);
		free_all(&g);
		return (0);
	}
	mainframe(&g);
	free_all(&g);
	return (0);
}
