#include "../incs/lem_in.h"

int			check_start_end_count_apx(int i, t_graph *g)
{
	if (i != g->napex)
		return (0);
	if (g->start == -1 || g->end == -1)
		return (0);
	return (1);
}

int			check_start_end(int *name, t_graph *g)
{
	if (*name > -1)
	{
		g->error = -1;
		return (1);
	}
	*name = g->napex;
	return (0);
}

int			ft_input_checker(t_graph *g, char *line)
{
	if (!ft_strcmp("##start", line))
		return (check_start_end(&g->start, g));
	else if (!ft_strcmp("##end", line))
		return (check_start_end(&g->end, g));
	else if (!ft_strncmp("##", line, 2))
	{
		g->error = -1;
		return (1);
	}
	else if (!ft_strncmp("#", line, 1))
		return (0);
	else if (!ft_strchr(line, '-'))
		++g->napex;
	return (1);
}

int			d_checker(char *example, t_list *lst)
{
	while (lst)
	{
		if (!ft_strcmp_bif(example, lst->content, ' ', 1))
			return (0);
		lst = lst->next;
	}
	return (1);
}

int			check_doubles(t_list *lst, t_graph *g)
{
	int		i;

	i = 1;
	while (lst->next->next && i < g->napex)
	{
		if (i < g->napex && !d_checker(lst->next->content, lst->next->next))
			return (0);
		lst = lst->next;
		++i;
	}
	return (1);
}
