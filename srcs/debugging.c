#include "../incs/lem_in.h"

t_list		*free_char_ptr_lst(char *ptr)
{
	ft_memdel((void*)&ptr);
	return (NULL);
}

int			ft_lst_int_del(t_list **dlst, void (*del)(void *, size_t), int out)
{
	ft_lstdel(dlst, del);
	return (out);
}

void		print_paths(t_graph *g)
{
	int		i;
	t_list	*p;
	t_list	*temp;

	i = -1;
	p = g->dif;
	ft_printf("Paths:\n");
	while (p)
	{
		++i;
		temp = p->content;
		ft_printf("way %d : len - [%lu] ", i, temp->content_size);
		temp = temp->next;
		while (temp)
		{
			ft_printf("(%lu)", temp->content_size);
			temp = temp->next;
		}
		ft_printf("\n");
		p = p->next;
	}
	ft_printf("\n");
}

void		print_graph(t_graph *g)
{
	int		i;
	t_list	*temp;

	i = -1;
	temp = NULL;
	ft_printf("Graph:\nants -- %d\n", g->ant);
	while (g->apxs[++i])
	{
		ft_printf("ind - %d name - "
		"%-10s x - %2d y - %2d neig -- ", i, g->apxs[i]->name,
				g->apxs[i]->coord.x, g->apxs[i]->coord.y);
		temp = g->apxs[i]->next;
		while (temp)
		{
			ft_printf("%5s", g->apxs[temp->content_size]->name);
			temp = temp->next;
		}
		ft_printf("\n");
	}
	ft_printf("\n");
}

void		print_res_ways(t_list *res, t_list **ways, t_graph *g)
{
	int		i;
	t_list	*temp;

	i = 0;
	res = res->next;
	ft_printf("Result_ways:\n");
	while (res)
	{
		temp = ways[res->content_size];
		ft_printf("way %d : len - [%lu] ", i, temp->content_size);
		temp = temp->next;
		while (temp)
		{
			ft_printf("(%s)", g->apxs[temp->content_size]->name);
			temp = temp->next;
		}
		++i;
		ft_printf("\n");
		res = res->next;
	}
	ft_printf("\n");
}
