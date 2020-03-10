#include "vlenin.h"

void	graph_draw_start_end(t_graph *g, int i)
{
	SDL_Rect	place;
	SDL_Texture	*texture;
	int			size;

	texture = NULL;
	size = (i == g->start) ? 100 : 200;
	if (i == g->start)
		texture = g_vi->star_texture;
	if (i == g->end)
		texture = g_vi->black_hole_texture;
	place.x = g->apxs[i]->coord.x - size / 3;
	place.y = g->apxs[i]->coord.y - size / 3;
	place.w = size;
	place.h = size;
	if ((SDL_RenderCopyEx(g_vi->grenderer, texture, NULL, &place,
			g_vi->tasmanian, NULL, SDL_FLIP_NONE) < 0))
		close_window();
}

void	draw_links(t_graph *g, t_list *iter, int i)
{
	SDL_SetRenderDrawColor(g_vi->grenderer, 0x2B, 0x73, 0xC4, 0xFF);
	while (iter)
	{
		SDL_RenderDrawLine(g_vi->grenderer,
				g->apxs[i]->coord.x + 25,
				g->apxs[i]->coord.y + 25,
				g->apxs[iter->content_size]->coord.x + 25,
				g->apxs[iter->content_size]->coord.y + 25);
		iter = iter->next;
	}
}

void	create_planets(t_graph *g, int i)
{
	SDL_Texture	*object;
	SDL_Rect	place_for_planets;

	g_vi->tasmanian += (i % 2) ? 15 : -15;
	place_for_planets.x = g->apxs[i]->coord.x;
	place_for_planets.y = g->apxs[i]->coord.y;
	place_for_planets.w = 50;
	place_for_planets.h = 50;
	object = (i % 2) ? g_vi->planet_red_texture : g_vi->planet_grey_texture;
	if ((SDL_RenderCopyEx(g_vi->grenderer, object, NULL,
			&place_for_planets, 0, NULL, SDL_FLIP_NONE) < 0))
		close_window();
}

int		graph_draw(t_graph *g)
{
	int		i;
	t_list	*temp;

	i = -1;
	while (++i < g->napex)
	{
		temp = g->apxs[i]->next;
		draw_links(g, temp, i);
		create_planets(g, i);
		if (i == g->end || i == g->start)
		{
			graph_draw_start_end(g, i);
			continue ;
		}
	}
	return (g_vi->success);
}
