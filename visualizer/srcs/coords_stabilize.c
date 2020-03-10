#include "vlenin.h"

void		find_minmax_coords(t_graph *g, t_viz *vi)
{
	int i;

	i = -1;
	vi->min.x = INT32_MAX;
	vi->min.y = INT32_MAX;
	vi->max.x = INT32_MIN;
	vi->max.y = INT32_MIN;
	while (++i < g->napex)
	{
		if (g->apxs[i]->coord.x < vi->min.x)
			vi->min.x = g->apxs[i]->coord.x;
		if (g->apxs[i]->coord.y < vi->min.y)
			vi->min.y = g->apxs[i]->coord.y;
		if (g->apxs[i]->coord.x > vi->max.x)
			vi->max.x = g->apxs[i]->coord.x;
		if (g->apxs[i]->coord.y > vi->max.y)
			vi->max.y = g->apxs[i]->coord.y;
	}
}

void		coords_stabilize(t_graph *g)
{
	int i;

	i = -1;
	while (++i < g->napex)
	{
		g->apxs[i]->coord.x = (g_vi->min.x < 0) ?
				g->apxs[i]->coord.x + g_vi->min.x :
				g->apxs[i]->coord.x - g_vi->min.x;
		g->apxs[i]->coord.y = (g_vi->min.y < 0) ?
				g->apxs[i]->coord.y + g_vi->min.y :
				g->apxs[i]->coord.y - g_vi->min.y;
	}
	find_minmax_coords(g, g_vi);
}

void		apxs_coords_rw_to_rel(t_graph *g, t_viz *vi)
{
	int i;

	i = -1;
	while (++i < g->napex)
	{
		g->apxs[i]->coord.x = (g->apxs[i]->coord.x * RELATIVE_DIVISION_RATIO)
				/ (vi->min.x + vi->max.x);
		g->apxs[i]->coord.y = (g->apxs[i]->coord.y * RELATIVE_DIVISION_RATIO)
				/ (vi->min.y + vi->max.y);
	}
}

void		apxs_coord_rel_to_abs(t_graph *g)
{
	int i;

	i = -1;
	while (++i < g->napex)
	{
		g->apxs[i]->coord.x = MAP_WIDTH / RELATIVE_DIVISION_RATIO *
				g->apxs[i]->coord.x + MARGIN / 2;
		g->apxs[i]->coord.y = MAP_HEIGHT / RELATIVE_DIVISION_RATIO *
				g->apxs[i]->coord.y + MARGIN / 2;
	}
}
