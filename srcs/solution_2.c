#include "../incs/lem_in.h"

void		increase_pr(t_graph *g, t_list *path)
{
	t_list	*temp;

	temp = path->next;
	while (temp)
	{
		g->apxs[temp->content_size]->pr += 1;
		temp = temp->next;
	}
}

int			find_doubles(t_list *base, t_list *path, size_t end)
{
	t_list	*temp;

	temp = base;
	while (temp)
	{
		if (ft_lstcmp_cs(temp->content, path, end))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void		ft_lst_sort_add_cs(t_list **alst, t_list *new, size_t len)
{
	t_list	*temp;
	t_list	*prev;

	temp = *alst;
	prev = NULL;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	while (temp && ((t_list*)temp->content)->content_size < len)
	{
		prev = temp;
		temp = temp->next;
	}
	new->next = temp;
	if (prev)
		prev->next = new;
	else
	{
		new->next = *alst;
		*alst = new;
	}
}

int			get_path(t_graph *g)
{
	t_list	*path;
	t_list	*node_for_path;
	int		flag;

	path = NULL;
	flag = find_path(g, g->end, &path, 0);
	if (flag == -1)
		return (ft_lst_int_del(&path, ft_content_del, -1));
	else if (flag == 0 || path == NULL)
		return (ft_lst_int_del(&path, ft_content_del, 0));
	if (find_doubles(g->dif, path, (size_t)g->end))
	{
		increase_pr(g, path);
		return (ft_lst_int_del(&path, ft_content_del, 1));
	}
	if (!(node_for_path = ft_lstnew(NULL, 0)))
		return (ft_lst_int_del(&path, ft_content_del, -1));
	increase_pr(g, path);
	node_for_path->content = path;
	ft_lst_sort_add_cs(&g->dif, node_for_path, path->content_size);
	++g->path_count;
	return (1);
}
