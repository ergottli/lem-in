#include "../incs/lem_in.h"

int			get_name(t_list *lst, t_apex **new)
{
	t_apex	*temp;
	char	**arr;

	temp = *new;
	arr = NULL;
	arr = ft_strsplit(lst->content, ' ');
	if (!is_apex(arr))
		return (free_arr(arr));
	if (!(temp->name = ft_strdup(arr[0])))
		return (free_arr(arr));
	temp->coord.x = ft_atoi(arr[1]);
	temp->coord.y = ft_atoi(arr[2]);
	free_d_char_arr(arr, 0);
	temp->next = NULL;
	return (1);
}

t_apex		*new_apx(t_list *lst)
{
	t_apex	*new;

	if (!(new = (t_apex*)ft_memalloc(sizeof(t_apex))))
		return (0);
	new->stat = 0;
	new->pr = 0;
	if (!(get_name(lst, &new)))
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

int			rec_ap_data(t_graph *g, t_list *rfi)
{
	int		i;
	t_list	*temp;

	i = -1;
	temp = rfi;
	if (!rfi)
		return (0);
	if (!(g->apxs = (t_apex**)ft_memalloc(sizeof(t_apex*) * (g->napex + 1))))
		return (0);
	if (!ft_isnum(temp->content))
		return (0);
	if ((g->ant = ft_atoi(temp->content)) < 1)
		return (0);
	temp = temp->next;
	while (temp && ++i < g->napex)
	{
		g->apxs[i] = new_apx(temp);
		if (!g->apxs[i])
			return (0);
		temp = temp->next;
	}
	if (!sort_apxs(g) || !check_start_end_count_apx(i, g)
	|| !get_links(temp, g))
		return (0);
	return (1);
}

int			ft_input(t_graph *g)
{
	int		ret;
	int		len;
	char	*line;
	t_list	*temp;

	while ((ret = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		len = ft_strlen(line) + 1;
		temp = ft_lstnew(line, sizeof(char) * len);
		ft_lst_append(&g->input, temp);
		if (!ft_input_checker(g, line))
		{
			free(line);
			if (g->error)
				return (0);
			continue ;
		}
		temp = ft_lstnew(line, sizeof(char) * len);
		free(line);
		ft_lst_append(&g->dif, temp);
	}
	if (ret == -1 || !check_doubles(g->dif, g) || !rec_ap_data(g, g->dif))
		return (0);
	ft_lstdel(&g->dif, ft_content_del);
	return (1);
}
