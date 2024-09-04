NAME	=	cub3d

CC		=	cc -g
CFLAGS	=	-O3
# CFLAGS	=	-Wall -Werror -Wextra -O3 -flto
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	./MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a 

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

SRCDIR	=	./src
SRC		=	$(SRCDIR)/0_main.c \
			$(SRCDIR)/0_draw_images.c \
			$(SRCDIR)/0_init_images.c \
			$(SRCDIR)/0_init_structs.c \
			$(SRCDIR)/0_map_read.c \
			$(SRCDIR)/1_user_inputs.c \
			$(SRCDIR)/1_wasd_move.c \
			$(SRCDIR)/2_draw_minimap.c \
			$(SRCDIR)/2_draw_raycast.c \
			$(SRCDIR)/2_rotate_camera.c \
			$(SRCDIR)/utils_calc.c \
			$(SRCDIR)/utils_draw.c \
			$(SRCDIR)/utils_free.c \
			$(SRCDIR)/utils_test.c

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(LIBMLX) $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -df $(OBJDIR)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(LFTDIR)/libft.a
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all clean fclean re
