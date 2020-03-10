#include "../incs/lem_in.h"

void			make_min(int *min, int n_min, t_list **mw, t_list *nw)
{
	*min = n_min;
	ft_lstdel(mw, ft_content_del);
	*mw = nw;
}

t_list			**indexing_ways(t_graph *g)
{
	int			i;
	t_list		*temp;
	t_list		**ways;

	i = -1;
	temp = g->dif;
	if (!(ways = (t_list**)malloc(sizeof(t_list*) * g->path_count)))
		return (NULL);
	while (++i < g->path_count)
	{
		ways[i] = temp->content;
		temp = temp->next;
	}
	return (ways);
}

t_list			**sort_ways(t_graph *g)
{
	t_list		*res;
	t_list		**ways;

	res = NULL;
	ways = NULL;
	if (!g->dif)
		return (NULL);
	if (!(ways = indexing_ways(g)))
		return (0);
	if (!(res = comb_ways(g, ways)))
	{
		free(ways);
		return (0);
	}
	g->res = res;
	return (ways);
}
