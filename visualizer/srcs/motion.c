#include "vlenin.h"

int		make_step(t_point coord, int ship_id)
{
	g_vi->ships[ship_id].x = coord.x - 50;
	g_vi->ships[ship_id].y = coord.y - 50;
	g_vi->ships[ship_id].w = 100;
	g_vi->ships[ship_id].h = 100;
	if ((SDL_RenderCopy(g_vi->grenderer,
			g_vi->ship_texture, NULL, &g_vi->ships[ship_id]) < 0))
	{
		ft_printf("error\n");
		return (0);
	}
	return (1);
}

void	count_angle(void)
{
	int i;

	i = -1;
	while (g_vi->sh_in_move[++i])
	{
		g_vi->distance[g_vi->sh_in_move[i]].x =
				abs(g_vi->destination[g_vi->sh_in_move[i]].x
				- g_vi->current[g_vi->sh_in_move[i]].x);
		g_vi->offset[g_vi->sh_in_move[i]].x =
				(g_vi->current[g_vi->sh_in_move[i]].x
				< g_vi->destination[g_vi->sh_in_move[i]].x) ? 1 : -1;
		g_vi->distance[g_vi->sh_in_move[i]].y =
				abs(g_vi->destination[g_vi->sh_in_move[i]].y
				- g_vi->current[g_vi->sh_in_move[i]].y);
		g_vi->offset[g_vi->sh_in_move[i]].y =
				(g_vi->current[g_vi->sh_in_move[i]].y <
		g_vi->destination[g_vi->sh_in_move[i]].y) ? 1 : -1;
		g_vi->angle[g_vi->sh_in_move[i]] =
				((g_vi->distance[g_vi->sh_in_move[i]].x >
				g_vi->distance[g_vi->sh_in_move[i]].y) ?
				g_vi->distance[g_vi->sh_in_move[i]].x :
				-g_vi->distance[g_vi->sh_in_move[i]].y) / 2;
	}
}

int		path_is_complete(void)
{
	int i;
	int complete_all;

	i = -1;
	complete_all = 1;
	while (g_vi->sh_in_move[++i])
	{
		if (g_vi->current[g_vi->sh_in_move[i]].x
		!= g_vi->destination[g_vi->sh_in_move[i]].x &&
			g_vi->current[g_vi->sh_in_move[i]].y
			!= g_vi->destination[g_vi->sh_in_move[i]].y)
			complete_all = 0;
	}
	return (complete_all);
}

void	motion(t_graph *g)
{
	int			i;
	SDL_Rect	rect_for_bg;

	count_angle();
	while (!path_is_complete())
	{
		i = -1;
		SDL_RenderClear(g_vi->grenderer);
		if ((g_vi->quit = catch_events(g_vi->event)))
			close_window();
		rect_for_bg = (SDL_Rect){0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
		SDL_RenderCopy(g_vi->grenderer,
				g_vi->texture_background, NULL, &rect_for_bg);
		graph_draw(g);
		while (g_vi->sh_in_move[++i])
			make_step(g_vi->current[g_vi->sh_in_move[i]],
					g_vi->sh_in_move[i]);
		SDL_RenderPresent(g_vi->grenderer);
		i = -1;
		while (g_vi->sh_in_move[++i])
			g_vi->current[g_vi->sh_in_move[i]] =
			brasenham(g_vi->current[g_vi->sh_in_move[i]],
			g_vi->destination[g_vi->sh_in_move[i]], g_vi->sh_in_move[i]);
		g_vi->tasmanian += 0.1;
	}
}

void	path_draw(t_graph *g)
{
	t_list	*res_iter;
	t_list	*path_iter;
	t_point	*apx_ind;
	int		i;

	res_iter = g->res;
	g_vi->tasmanian = 0;
	while (res_iter)
	{
		i = -1;
		path_iter = (t_list*)res_iter->content;
		while (path_iter)
		{
			apx_ind = (t_point*)path_iter->content;
			g_vi->destination[apx_ind->x] = g->apxs[apx_ind->y]->coord;
			if (g_vi->current[apx_ind->x].x == INT32_MIN
			&& g_vi->current[apx_ind->x].y == INT32_MIN)
				g_vi->current[apx_ind->x] = g->apxs[g->start]->coord;
			g_vi->sh_in_move[++i] = apx_ind->x;
			path_iter = path_iter->next;
		}
		motion(g);
		ft_bzero(g_vi->sh_in_move, MAX_SHIPS);
		res_iter = res_iter->next;
	}
}
