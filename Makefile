NAME = lem-in

SRCS = ./srcs/

SRC = $(SRCS)main.c $(SRCS)input_data.c \
    $(SRCS)input_data_2.c $(SRCS)input_data_3.c \
    $(SRCS)input_data_4.c $(SRCS)debugging.c \
    $(SRCS)solution.c $(SRCS)solution_2.c \
    $(SRCS)sort_ways.c $(SRCS)print_result.c \
    $(SRCS)print_result_2.c $(SRCS)sort_ways_2.c \
    $(SRCS)sort_apxs.c $(SRCS)bonus.c
SRCO = ./main.o ./debugging.o ./input_data.o ./input_data_2.o \
    ./input_data_3.o ./input_data_4.o ./solution_2.o  ./sort_ways.o \
    ./solution.o ./sort_ways_2.o ./print_result.o ./print_result_2.o \
    ./sort_apxs.o ./bonus.o

all: $(NAME)

$(NAME):
	make -C libft/ fclean && make -C libft/
	clang -Wall -Wextra -Werror -I libft/includes -c $(SRC)
	clang -o $(NAME) $(SRCO) -I libft/includes -L libft/ -lft

clean:
	rm -f *.o
	rm -rf ./libft/*.o
	rm -rf ./libft/libft.a

fclean: clean
	rm -f $(NAME)

gdb: fclean
	make -C libft/ fclean && make -C libft/
	gcc -g $(SRC) -I libft/includes -L libft/ -lft -o debugg

re: fclean all
