#ifndef V_LEM_IN_H
# define V_LEM_IN_H

# include "../libft/libft.h"
# include <limits.h>
# include <stdio.h>

# define K g->start

typedef struct			s_apex
{
	unsigned char		stat;
	char				*name;
	size_t				pr;
	t_point				coord;
	t_list				*next;
}						t_apex;

typedef struct			s_graph
{
	t_apex				**apxs;
	t_list				*dif;
	int					*parents;
	t_list				*res;
	t_list				*input;
	int					path_count;
	int					ord;
	int					napex;
	int					start;
	int					end;
	int					ant;
	unsigned char		error;
	int					flag;
	unsigned char		next_parse;
}						t_graph;

/*
** -------------------------- Input functions ------------------------------
*/

int						ft_input(t_graph *g);
int						parse_arg(char **argv, t_graph *g);
int						get_links(t_list *temp, t_graph *g);
int						arr_count(char **arr, int n);
int						free_arr(char **arr);
int						check_doubles(t_list *lst, t_graph *g);
int						ft_input_checker(t_graph *g, char *line);
int						check_start_end_count_apx(int i, t_graph *g);
int						is_apex(char **arr);
int						sort_apxs(t_graph *g);
int						bin_search(t_apex **apxs, char *name, int min, int max);
int						ft_inp_com(t_graph *g);

#endif
