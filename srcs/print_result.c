#include "../incs/lem_in.h"

int			ft_comb_len(t_graph *g, t_list **ways)
{
	int		len;
	t_list	*temp;

	len = 0;
	temp = g->res->next;
	g->path_count = 0;
	while (temp)
	{
		len += ways[temp->content_size]->content_size;
		temp = temp->next;
		++g->path_count;
	}
	return (len);
}

void		additional_lem(t_graph *g, t_list **ways, t_list *l_w, int an)
{
	t_list	*res_iter;
	t_list	*len_iter;
	size_t	min_way;

	min_way = 0;
	while (an)
	{
		MIN_K = INT32_MAX;
		res_iter = g->res->next;
		len_iter = l_w;
		while (res_iter)
		{
			K = len_iter->content_size +
					ways[res_iter->content_size]->content_size - 1;
			if (K < MIN_K)
			{
				MIN_K = K;
				min_way = res_iter->content_size;
			}
			len_iter = len_iter->next;
			res_iter = res_iter->next;
		}
		++ways[min_way]->content_size;
		--an;
	}
}

void		calc_lem_per_way(t_graph *g, t_list **ways, t_list *len_ways)
{
	int		sum;
	int		ants;
	t_list	*temp;

	ants = g->ant;
	sum = g->ant + ft_comb_len(g, ways);
	temp = g->res->next;
	while (temp)
	{
		ways[temp->content_size]->content_size = (sum / g->path_count)
					- ways[temp->content_size]->content_size;
		ants -= ways[temp->content_size]->content_size;
		temp = temp->next;
	}
	if (ants > 0)
		additional_lem(g, ways, len_ways, ants);
}

t_list		*make_list_len_ways(t_graph *g, t_list **ways)
{
	t_list	*res_iter;
	t_list	*len_ways;
	t_list	*temp;

	len_ways = NULL;
	res_iter = g->res->next;
	while (res_iter)
	{
		if (!(temp = ft_lstnew(NULL,
				ways[res_iter->content_size]->content_size)))
		{
			ft_lstdel(&len_ways, ft_content_del);
			return (NULL);
		}
		ft_lst_append(&len_ways, temp);
		res_iter = res_iter->next;
	}
	return (len_ways);
}

void		print_result(t_graph *g, t_list **ways)
{
	int		i;
	int		l_in_end;
	t_list	*len_ways;

	i = 0;
	l_in_end = 0;
	ft_lst_print(g->input, 1u << 5u, 1);
	ft_putchar('\n');
	len_ways = make_list_len_ways(g, ways);
	calc_lem_per_way(g, ways, len_ways);
	make_zero_pr(g);
	g->error = 0;
	while (l_in_end < g->ant)
	{
		(g->error && g->path_count == 1 && len_ways->content_size == 1)
		? ft_putchar(' ') : 0;
		make_move(&i, &l_in_end, g, ways);
		if (g->path_count != 1 || len_ways->content_size != 1)
			ft_putchar('\n');
		++g->error;
	}
	if (g->path_count == 1 && len_ways->content_size == 1)
		ft_putchar('\n');
	print_bonus(g, ways, len_ways->content_size);
	ft_lstdel(&len_ways, ft_content_del);
}
