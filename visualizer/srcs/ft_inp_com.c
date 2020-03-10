#include "../incs/vlenin.h"

t_list		*get_command(char *s, t_graph *g)
{
	t_list	*node;
	t_point *ant_room;

	node = NULL;
	if (s[0] != 'L')
		return (0);
	if (!(node = ft_lstnew(NULL, sizeof(long))))
		return (NULL);
	if (!(ant_room = (t_point*)malloc(sizeof(t_point))))
	{
		free(node);
		return (0);
	}
	ant_room->x = ft_atoi(s + 1);
	ant_room->y = bin_search(g->apxs, ft_strchr(s, '-') + 1, 0, g->napex - 1);
	if (ant_room->x < 1 || ant_room->y < 0)
	{
		free(node);
		free(ant_room);
		return (0);
	}
	node->content = ant_room;
	return (node);
}

t_list		*free_list(t_list *list)
{
	if (!list)
		return (NULL);
	free(list);
	return (NULL);
}

t_list		*get_line(char *s, t_graph *g)
{
	t_list	*node_com;
	t_list	*temp;
	t_list	*res;
	char	**arr;

	node_com = NULL;
	if (!(res = ft_lstnew(NULL, sizeof(long))))
		return (0);
	if (!(arr = ft_strsplit(s, ' ')))
	{
		free(res);
		return (0);
	}
	while (*arr)
	{
		if (!(temp = get_command(*arr, g)))
		{
			ft_lstdel(&node_com, ft_content_del);
			return (free_list(res));
		}
		ft_lstadd(&node_com, temp);
		++arr;
	}
	res->content = node_com;
	return (res);
}

int			ft_inp_com(t_graph *g)
{
	t_list	*inp_iter;
	t_list	*temp;

	if (!g->input)
		return (0);
	inp_iter = g->input->next;
	while (inp_iter)
	{
		if (!(temp = get_line(inp_iter->content, g)))
			return (0);
		ft_lst_append(&g->res, temp);
		inp_iter = inp_iter->next;
	}
	return (1);
}
