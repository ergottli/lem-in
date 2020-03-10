#include "../incs/lem_in.h"

int			get_com(char *str, t_graph *g)
{
	if (!ft_strcmp(str, "-g"))
	{
		g->bonus |= PRINT_GRAPH;
		return (1);
	}
	else if (!ft_strcmp(str, "-p"))
	{
		g->bonus |= PRINT_PATHS;
		return (1);
	}
	else if (!ft_strcmp(str, "-r"))
	{
		g->bonus |= PRINT_RES;
		return (1);
	}
	else if (!ft_strcmp(str, "-s"))
	{
		g->bonus |= PRINT_STEPS;
		return (1);
	}
	return (0);
}

int			parse_arg(char **argv, t_graph *g)
{
	int		i;

	i = 0;
	while (argv[++i])
	{
		if (!get_com(argv[i], g))
		{
			ft_putendl("usage: -g -- graph -p "
	"-- paths -r -- result_paths -s -- steps");
			return (0);
		}
	}
	return (1);
}

void		print_bonus(t_graph *g, t_list **ways, size_t len_way)
{
	if (PRINT_GRAPH & g->bonus)
		print_graph(g);
	if (PRINT_PATHS & g->bonus)
		print_paths(g);
	if (PRINT_RES & g->bonus)
		print_res_ways(g->res, ways, g);
	if (g->error && g->path_count == 1 && len_way < 2)
		g->res->content_size = 1;
	if (PRINT_STEPS & g->bonus)
		ft_printf("Steps:\n%lu\n", g->res->content_size);
}
