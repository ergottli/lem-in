#include "../incs/lem_in.h"

void			ft_add_to_table(char **table, t_list *way)
{
	t_list		*start;

	start = way->next->next;
	while (start->next)
	{
		table[0][start->content_size] = 1;
		start = start->next;
	}
}

int				is_intersec(const char *table, t_list *way)
{
	way = way->next->next;
	while (way->next)
	{
		if (table[way->content_size] == 1)
			return (1);
		way = way->next;
	}
	return (0);
}

int				ft_get_ind(t_list *path, int i, int ants, t_list **ways)
{
	int			len;
	int			k;
	int			res;

	len = 0;
	k = 0;
	path = path->next;
	while (path)
	{
		++k;
		len += ways[path->content_size]->content_size;
		path = path->next;
	}
	++k;
	len += ways[i]->content_size;
	res = ((ants + len) % k != 0) ?
		(ants + len) / k : (ants + len) / k - 1;
	return (res);
}

t_list			*find_comb(t_graph *g, int i, char **table, t_list **ways)
{
	t_list		*temp;
	t_list		*path;
	int			k;
	int			path_count;

	path_count = 0;
	k = INT32_MAX;
	path = ft_lstnew(NULL, INT32_MAX);
	while ((int)path->content_size > 0 && ++i < g->path_count)
	{
		if (is_intersec(table[0], ways[i]))
			continue ;
		k = ft_get_ind(path, i, g->ant, ways);
		if (k > (int)path->content_size)
			break ;
		path->content_size = k;
		temp = ft_lstnew(NULL, i);
		ft_lst_append(&path, temp);
		ft_add_to_table(table, ways[i]);
		++path_count;
		if (path_count >= g->ant)
			break ;
	}
	return (path);
}

t_list			*comb_ways(t_graph *g, t_list **ways)
{
	int			i;
	int			min;
	char		*intеrsec_table;
	t_list		*min_way;
	t_list		*new_way;

	i = 0;
	min = INT32_MAX;
	min_way = NULL;
	new_way = NULL;
	if (!(intеrsec_table = ft_strnew(sizeof(char) * g->napex)))
		return (NULL);
	while (i < g->path_count && i < MAX_WAY)
	{
		if (!(new_way = find_comb(g, i - 1, &intеrsec_table, ways)))
			return (free_char_ptr_lst(intеrsec_table));
		if ((int)new_way->content_size < min)
			make_min(&min, (int)new_way->content_size, &min_way, new_way);
		else
			ft_lstdel(&new_way, ft_content_del);
		ft_bzero(intеrsec_table, sizeof(char) * g->napex);
		++i;
	}
	free(intеrsec_table);
	return (min_way);
}
