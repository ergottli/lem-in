#include "vlenin.h"

t_point		brasenham(t_point current, t_point destination, int ship)
{
	int	step;

	step = g_vi->angle[ship];
	if (current.x == destination.x && current.y == destination.y)
		return (destination);
	if (step > -g_vi->distance[ship].x)
	{
		g_vi->angle[ship] -= g_vi->distance[ship].y;
		current.x += g_vi->offset[ship].x;
	}
	if (step < g_vi->distance[ship].y)
	{
		g_vi->angle[ship] += g_vi->distance[ship].x;
		current.y += g_vi->offset[ship].y;
	}
	return (current);
}
