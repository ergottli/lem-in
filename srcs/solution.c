#include "../incs/lem_in.h"

int				*bfs(t_graph *g)
{
	int			cur;
	t_desdlist	*deq;
	t_list		*temp;

	deq = ft_create_desdlist();
	ft_deq_push_l(&deq, NULL, g->start);
	while (!ft_deq_isempty(deq))
	{
		cur = ft_deq_popcs_r(&deq);
		temp = g->apxs[cur]->next;
		while (temp)
		{
			if (!(g->apxs[temp->content_size]->stat & DISC ||
			(g->apxs[temp->content_size]->stat & NO_FS && cur == g->start)))
			{
				g->apxs[temp->content_size]->stat |= DISC;
				ft_deq_push_l_pr(&deq, NULL,
						temp->content_size, g->apxs[temp->content_size]->pr);
				g->parents[temp->content_size] = cur;
			}
			temp = temp->next;
		}
	}
	ft_deq_del(&deq);
	return (g->parents);
}

int				find_path(t_graph *g, int end, t_list **res, int i)
{
	t_list		*temp;

	if (!(temp = ft_lstnew(NULL, 0)))
		return (ft_lst_int_del(res, ft_content_del, -1));
	temp->content_size = end;
	ft_lstadd(res, temp);
	if (g->start == end)
	{
		if (!(temp = ft_lstnew(NULL, 0)))
			return (ft_lst_int_del(res, ft_content_del, -1));
		temp->content_size = i;
		ft_lstadd(res, temp);
		return (1);
	}
	else if (end == -1)
		return (ft_lst_int_del(res, ft_content_del, 0));
	else
		find_path(g, g->parents[end], res, ++i);
	return (1);
}

void			status_correction(t_graph *g)
{
	t_list		*temp;
	int			i;

	i = -1;
	g->st_neigh = 0;
	while (++i < g->napex)
		g->apxs[i]->stat = 0;
	temp = g->apxs[g->start]->next;
	while (temp)
	{
		if (!(g->apxs[temp->content_size]->stat & DISC))
			++g->st_neigh;
		temp = temp->next;
	}
	g->apxs[g->start]->stat |= DISC;
}

void			init_par(int *par, int len, int num)
{
	while (--len)
		par[len] = num;
}

int				ft_solution(t_graph *g)
{
	int			flag;
	int			max;

	flag = 0;
	if (!(g->parents = malloc(sizeof(int) * g->napex)))
		return (0);
	status_correction(g);
	max = (g->ant < g->napex) ? (g->ant * 2) : (g->napex * 2);
	while (max--)
	{
		init_par(g->parents, g->napex, -1);
		g->parents = bfs(g);
		flag = get_path(g);
		if (flag == -1)
			return (0);
		else if (flag == 0)
			break ;
		status_correction(g);
	}
	if (!g->dif)
		return (0);
	return (1);
}
