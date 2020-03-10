#include "vlenin.h"

int				free_arr(char **arr)
{
	free_d_char_arr(arr, 0);
	return (0);
}

void			make_link(t_graph *g, int a, int b, int f)
{
	t_list		*temp;

	temp = ft_lstnew(NULL, 0);
	temp->content_size = (size_t)b;
	ft_lst_append(&(g->apxs[a]->next), temp);
	if (f == 0)
		make_link(g, b, a, 1);
}

int				is_link(char **arr)
{
	if (!arr_count(arr, 2))
		return (0);
	if (!arr[0] || arr[0][0] == 'L')
		return (0);
	if (!arr[1] || arr[1][0] == 'L')
		return (0);
	return (1);
}

int				get_links(t_list *temp, t_graph *g)
{
	char		**arr;
	int			a;
	int			b;

	while (temp)
	{
		g->input = temp;
		if ((*((char*)temp->content)) == '\0')
			return (ft_next_parse(g));
		if (count_chars(temp->content, '-') != 1)
			return (0);
		arr = ft_strsplit(temp->content, '-');
		if (!is_link(arr))
			return (free_arr(arr));
		if ((a = bin_search(g->apxs, arr[0], 0, g->napex - 1)) == -1)
			return (free_arr(arr));
		if ((b = bin_search(g->apxs, arr[1], 0, g->napex - 1)) == -1)
			return (free_arr(arr));
		make_link(g, a, b, g->ord);
		temp = temp->next;
		free_d_char_arr(arr, 2);
	}
	return (1);
}
