#include "../incs/lem_in.h"

void		make_zero_pr(t_graph *g)
{
	int		i;

	i = -1;
	while (++i < g->napex)
		g->apxs[i]->pr = 0;
}

void		print_cur_move(int lem, char *apx, t_graph **g)
{
	if (!(*g)->st_neigh)
		ft_printf(" L%d-%s", lem, apx);
	else
		ft_printf("L%d-%s", lem, apx);
	(*g)->st_neigh = 0;
}

int			recursive_mp_ants(int i, int *l_in_end, t_list **path, t_graph **g)
{
	t_list	*temp;
	size_t	ant;
	int		flag;

	temp = *path;
	if (temp == NULL)
	{
		if ((*g)->st_neigh == 0)
			return (1);
		else
			return (0);
	}
	ant = (*g)->apxs[temp->content_size]->pr;
	(*g)->apxs[temp->content_size]->pr = i;
	if (i && !temp->next)
		++(*l_in_end);
	flag = recursive_mp_ants(ant, l_in_end, &(temp->next), g);
	if (i && temp->content_size != (size_t)(*g)->start)
		print_cur_move(i, (*g)->apxs[temp->content_size]->name, g);
	return (flag);
}

void		move_print_ant(int *i, int *l_in_end, t_graph *g, t_list **path)
{
	t_list	*temp;

	temp = *path;
	if (temp->content_size)
	{
		++(*i);
		--temp->content_size;
		recursive_mp_ants(*i, l_in_end, &(temp->next->next), &g);
	}
	else
		recursive_mp_ants(0, l_in_end, &(temp->next->next), &g);
}

void		make_move(int *i, int *l_in_end, t_graph *g, t_list **ways)
{
	t_list	*temp;

	temp = g->res->next;
	g->st_neigh = 1;
	while (temp)
	{
		move_print_ant(i, l_in_end, g, &ways[temp->content_size]);
		temp = temp->next;
	}
}
