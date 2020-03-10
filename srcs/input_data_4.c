#include "../incs/lem_in.h"

int			arr_count(char **arr, int n)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		++i;
	if (i != n)
		return (0);
	return (1);
}

int			is_apex(char **arr)
{
	if (!arr_count(arr, 3))
		return (0);
	if (!arr[0] || arr[0][0] == 'L' || arr[0][0] == ' ')
		return (0);
	if (!ft_isnum(arr[1]) || !ft_isnum(arr[2]))
		return (0);
	return (1);
}
