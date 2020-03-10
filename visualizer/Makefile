#!/usr/bin/make

NAME =			v-lem-in
SRCS =			./srcs/
LIB =			./lib
LIB64 =			./lib64
LIBFT = 		$(LIB)/libft.a
SDL2 = 			$(LIB)/libSDL2.a
SDL2_image = 	$(LIB)/libSDL2_image.a
SRC =			$(SRCS)main.c \
				$(SRCS)init.c \
				$(SRCS)sdl_operate.c \
				$(SRCS)coords_stabilize.c \
				$(SRCS)graph_draw.c \
				$(SRCS)motion.c \
				$(SRCS)input_data.c \
				$(SRCS)input_data_2.c \
				$(SRCS)input_data_3.c \
				$(SRCS)input_data_4.c \
				$(SRCS)sort_apxs.c \
				$(SRCS)ft_inp_com.c \
				$(SRCS)motion_2.c
SRCO =			./main.o
DIRECTORY =		$(shell pwd)
FLAGS =			-Wall -Wextra -Werror

all: $(NAME)

$(LIBFT):
	mkdir -p lib
	make -C libft re; cp libft/libft.a lib/libft.a

DYLD: 
	export DYLD_LIBRARY_PATH=$(DIRECTORY)/lib

$(NAME): $(LIBFT) $(SDL2) $(SDL2_image)
	$(info Building visualizer based on SDL2 libs)
	gcc $(FLAGS) $(SRC) -I./libft -I./incs -L ./lib -lft -lSDL2 -lSDL2_image -o $(NAME)
	$(DYLD)
	export DYLD_LIBRARY_PATH=$(DIRECTORY)/lib
	$(DYLD)

linux: $(LIBFT)
	$(info Building visualizer based on SDL2 libs)
	mkdir -p lib
	gcc -I./incs -I./libft/includes -L./lib -lSDL2 -lSDL2_image -lft -lftprintf $(SRC) -o $(NAME)

$(SDL2):
	tar -xvf SDL2-2.0.10.tar.gz
	mv SDL2-2.0.10 SDL2
	mkdir -p lib
	cd SDL2; ./configure --prefix=$(DIRECTORY); $(MAKE) all;
	$(MAKE) -sC $(DIRECTORY)/SDL2 install

$(SDL2_image):
	tar -xvf SDL2_image-2.0.5.tar.gz
	mv SDL2_image-2.0.5 SDL2_image
	cd SDL2_image; ./configure --prefix=$(DIRECTORY); $(MAKE) all;
	$(MAKE) -sC $(DIRECTORY)/SDL2_image install

image:
	gcc -L./lib srcs/v-init.c -I ./incs -o image

clean:
	rm -f *.o
	make -C libft clean
	make -C SDL2 clean

fclean: clean
	rm -rf $(NAME)
	rm -rf lib share bin SDL2 SDL2_image

re: fclean all

.PHONY: lib SDL2 SDL2_image
