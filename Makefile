CUB3D		:= cub3D

CC 			:=	cc
FLAGS 		:=	-Wall -Werror -Wextra -g3

LIBFT	 	:= ./libft

LIB			:=	$(LIBFT)/libft.a
LIBMLX      := ./MLX42
MLX_REPO    := https://github.com/codam-coding-college/MLX42.git
LIBS_MLX    := $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADERS 	:=	-I ./include -I $(LIBFT)

SRC_PUSH	:=	main key_hook renderizer texture_loader movement

OBJ_PUSH	:=	$(addprefix objects/, $(addsuffix .o, $(SRC_PUSH)))

all: libmlx make_libft $(CUB3D)

$(CUB3D): $(OBJ_PUSH)
	$(CC) $(OBJ_PUSH) $(LIBS_MLX) $(LIB) $(HEADERS) -o $(CUB3D) -lm

make_libft:
	$(MAKE) -C $(LIBFT)

objects/%.o: source/%.c | objects
	$(CC) $(FLAGS) -o $@ -c $< $(HEADERS) ; \
	echo "Compiling: $(notdir $<)"

objects:
	mkdir -p objects

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "Cloning MLX42 repository..."; \
		git clone $(MLX_REPO) $(LIBMLX); \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -rf objects

fclean: clean
	$(MAKE) -C $(LIBFT) fclean
	rm -rf $(CUB3D)

re: fclean all