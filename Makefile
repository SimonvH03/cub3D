NAME	=	cub3d

CC		=	cc
CFLAGS	=	-O3 -flto
CFLAGS	+=	-Wall -Werror -Wextra
# CFLAGS	+=	-g -Werror
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	./MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

HEADERS =	./cub3d.h \
			./defs.h \
			./paths.h \

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/initialise/draw_game_images.c \
			$(SRCDIR)/initialise/draw_menu_images.c \
			$(SRCDIR)/initialise/init_game_images.c \
			$(SRCDIR)/initialise/init_game_structs.c \
			$(SRCDIR)/initialise/init_menu_images.c \
			$(SRCDIR)/initialise/init_menu_structs.c \
			$(SRCDIR)/initialise/read_cub_elements.c \
			$(SRCDIR)/initialise/read_map_init_camera.c \
			$(SRCDIR)/user_interface/arrowkey_turn.c \
			$(SRCDIR)/user_interface/user_inputs.c \
			$(SRCDIR)/user_interface/view_manager.c \
			$(SRCDIR)/user_interface/wasd_move.c \
			$(SRCDIR)/frame_process/arithmetic.c \
			$(SRCDIR)/frame_process/draw_map_player.c \
			$(SRCDIR)/frame_process/draw_minimap_walls.c \
			$(SRCDIR)/frame_process/draw_raycast.c \
			$(SRCDIR)/frame_process/draw_texture_column.c \
			$(SRCDIR)/frame_process/modlx.c \
			# $(SRCDIR)/test.c

OBJDIR	=	./obj
OBJ		=	$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all:  $(NAME)

$(LIBMLX):
	cmake $(LMLXDIR) -B $(LMLXDIR)/build && make -C $(LMLXDIR)/build -j4

$(LIBFT):
	make -C $(LFTDIR) all -s

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(LIBMLX) $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LFTDIR)/libft.a
	rm -rf $(LMLXDIR)/build

re: fclean all

.PHONY: all clean fclean re