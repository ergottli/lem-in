#include "../incs/lem_in.h"

int			apx_cmp(char *s1, char *s2)
{
	int		dif_len;

	dif_len = ft_strlen(s1) - ft_strlen(s2);
	if (dif_len)
		return (dif_len);
	return (ft_strcmp(s1, s2));
}

int			bin_search(t_apex **apxs, char *name, int min, int max)
{
	int		mid;

	mid = (min + max) / 2;
	if (!apx_cmp(apxs[mid]->name, name))
		return (mid);
	else if (min >= max)
		return (-1);
	else if (apx_cmp(apxs[mid]->name, name) > 0)
		return (bin_search(apxs, name, min, mid - 1));
	else
		return (bin_search(apxs, name, mid + 1, max));
}

void		merge_apx(t_graph *g, t_apex **tmp, int l, int r)
{
	int		i;
	int		ll;
	int		mm;
	int		mid;

	i = l - 1;
	ll = l - 1;
	mid = (l + r) / 2;
	mm = mid;
	while (++ll < r)
		tmp[ll] = g->apxs[ll];
	ll = l;
	while (++i < r)
	{
		if (ll < mid && mm < r && apx_cmp(tmp[ll]->name, tmp[mm]->name) < 0)
			g->apxs[i] = tmp[ll++];
		else if (ll < mid && mm < r &&
		apx_cmp(tmp[ll]->name, tmp[mm]->name) > 0)
			g->apxs[i] = tmp[mm++];
		else if (ll == mid)
			g->apxs[i] = tmp[mm++];
		else
			g->apxs[i] = tmp[ll++];
	}
}

void		merge_sort_apx(t_graph *g, t_apex **tmp, int l, int r)
{
	int		mid;

	if (l == r - 1)
		return ;
	mid = (l + r) / 2;
	merge_sort_apx(g, tmp, l, mid);
	merge_sort_apx(g, tmp, mid, r);
	merge_apx(g, tmp, l, r);
}

int			sort_apxs(t_graph *g)
{
	char	*start;
	char	*end;
	t_apex	**temp;

	if (!g->apxs || !g->apxs[g->start] || !g->apxs[g->end])
		return (0);
	start = g->apxs[g->start]->name;
	end = g->apxs[g->end]->name;
	if (!(temp = (t_apex**)ft_memalloc(sizeof(t_apex*) * g->napex)))
		return (0);
	merge_sort_apx(g, temp, 0, g->napex);
	g->start = bin_search(g->apxs, start, 0, g->napex - 1);
	g->end = bin_search(g->apxs, end, 0, g->napex - 1);
	free(temp);
	return (1);
}
