#include "../incs/lem_in.h"

void		ft_graph_init(t_graph *g)
{
	g->apxs = NULL;
	g->dif = NULL;
	g->parents = NULL;
	g->res = NULL;
	g->input = NULL;
	g->st_neigh = 0;
	g->path_count = 0;
	g->start = -1;
	g->end = -1;
	g->napex = -1;
	g->ant = 0;
	g->ord = 0;
	g->error = 0;
	g->bonus = 0;
}

void		ft_graph_del(t_graph *g)
{
	int		i;

	i = -1;
	while (g->apxs[++i])
	{
		if (g->apxs[i]->name)
			free(g->apxs[i]->name);
		ft_lstdel(&g->apxs[i]->next, ft_content_del);
		ft_memdel((void*)&g->apxs[i]);
	}
	ft_memdel((void*)&g->apxs);
}

void		ft_del_lst_ways(t_graph *g)
{
	t_list	*dif_iter;

	dif_iter = g->dif;
	while (dif_iter)
	{
		ft_lstdel((void*)&(dif_iter->content), ft_content_del);
		dif_iter->content = NULL;
		dif_iter = dif_iter->next;
	}
	ft_lstdel(&g->dif, ft_content_del);
}

void		free_all(t_graph *g, int flag)
{
	if (flag)
		ft_lstdel(&g->dif, ft_content_del);
	else
		ft_del_lst_ways(g);
	ft_lstdel(&g->input, ft_content_del);
	if (g->apxs != NULL)
		ft_graph_del(g);
	if (g->parents != NULL)
		ft_memdel(((void*)&g->parents));
	if (g->res)
		ft_lstdel(&g->res, ft_content_del);
}

int			main(int argc, char **argv)
{
	t_graph g;
	t_list	**ways;

	ways = NULL;
	ft_graph_init(&g);
	if (argc > 1 && !parse_arg(argv, &g))
		return (0);
	if (!ft_input(&g))
	{
		ft_putendl("ERROR");
		free_all(&g, 1);
		return (0);
	}
	if (!ft_solution(&g))
	{
		ft_putendl("ERROR");
		free_all(&g, 0);
		return (0);
	}
	ways = sort_ways(&g);
	print_result(&g, ways);
	free_all(&g, 0);
	free(ways);
	return (0);
}
