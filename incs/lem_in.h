#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"
# include <limits.h>
# include <stdio.h>

# define DISC 128u
# define NO_FS 32u
# define MAX_WAY 22
# define K g->start
# define MIN_K g->end
# define PRINT_GRAPH 1u
# define PRINT_PATHS 2u
# define PRINT_RES 4u
# define PRINT_STEPS 8u

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
	int					st_neigh;
	int					path_count;
	int					ord;
	int					napex;
	int					start;
	int					end;
	int					ant;
	char				error;
	unsigned char		bonus;
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

/*
** -------------------------- Solution functions ----------------------------
*/

int						ft_solution(t_graph *g);
t_list					**sort_ways(t_graph *g);
void					init_par(int *par, int len, int num);
int						get_path(t_graph *g);
int						find_path(t_graph *g, int end, t_list **res, int i);
int						ft_lst_int_del(t_list **dlst,
		void (*del)(void *, size_t), int out);
t_list					*comb_ways(t_graph *g, t_list **ways);
void					make_min(int *min, int n_min, t_list **mw, t_list *nw);

/*
** -------------------------- Output functions ----------------------------
*/

void					print_result(t_graph *g, t_list **ways);
void					make_move(int *i, int *l_in_end,
		t_graph *g, t_list **ways);
void					make_zero_pr(t_graph *g);
void					print_bonus(t_graph *g, t_list **ways, size_t len_ways);

/*
** -------------------------- Debugging functions ----------------------------
*/

t_list					*free_char_ptr_lst(char *ptr);
void					print_list(t_list *rfi, t_graph *g);
void					print_graph(t_graph *g);
void					print_cs_list(t_list *lst);
void					print_int_path(t_graph *g);
void					print_paths(t_graph *g);
void					print_res_ways(t_list *res, t_list **ways, t_graph *g);
void					print_ants_per_way(t_list *res, t_list **ways);

#endif
