NAME	=	cub3D

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra
CFLAGS	+=	-g
# CFLAGS	+=	-O3
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a

LFTDIR	=	libft
LIBFT	=	$(LFTDIR)/libft.a

INCLDIR	=	. \
			./include \
			MLX42/include \
			libft

INCLUDE =	$(addprefix -I , $(INCLDIR))

SRCDIR	=	src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/error.c \
			$(SRCDIR)/gamestate/door_animation.c \
			$(SRCDIR)/gamestate/update_frametime.c \
			$(SRCDIR)/gamestate/weapon_animation.c \
			$(SRCDIR)/init/init_doors.c \
			$(SRCDIR)/init/init_game.c \
			$(SRCDIR)/init/init_hud.c \
			$(SRCDIR)/init/init_menu.c \
			$(SRCDIR)/init/init_player.c \
			$(SRCDIR)/init/init_weapon.c \
			$(SRCDIR)/init/init_window.c \
			$(SRCDIR)/init/new_images_bigmap.c \
			$(SRCDIR)/init/new_images_minimap.c \
			$(SRCDIR)/init/perimeter_check.c \
			$(SRCDIR)/init/read_elements.c \
			$(SRCDIR)/init/read_map.c \
			$(SRCDIR)/init/scalable.c \
			$(SRCDIR)/render/cast_ray.c \
			$(SRCDIR)/render/draw_texture_column.c \
			$(SRCDIR)/render/raycast.c \
			$(SRCDIR)/render/update_bigmap.c \
			$(SRCDIR)/render/update_minimap.c \
			$(SRCDIR)/user_interface/keyboard_controls.c \
			$(SRCDIR)/user_interface/keyhooks.c \
			$(SRCDIR)/user_interface/mouse_controls.c \
			$(SRCDIR)/user_interface/player_interaction.c \
			$(SRCDIR)/user_interface/select_button.c \
			$(SRCDIR)/user_interface/view_manager.c \
			$(SRCDIR)/utils/allocation_list.c \
			$(SRCDIR)/utils/arithmetic_float.c \
			$(SRCDIR)/utils/arithmetic_int.c \
			$(SRCDIR)/utils/gridmap_iter.c \
			$(SRCDIR)/utils/hudmap_setget_ability.c \
			$(SRCDIR)/utils/image_iter.c \
			$(SRCDIR)/utils/menu_scene_set_ability.c \
			$(SRCDIR)/utils/modlx.c \
			$(SRCDIR)/utils/normalize_vector2.c \
			$(SRCDIR)/utils/tilemap_cell.c \
			$(SRCDIR)/utils/tilemap_type.c \
			$(SRCDIR)/utils/transpore_texture.c


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
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(LIBMLX) $(LIBFT) $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) $(LIBMLX) $(MLXFLAGS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJDIR)
	make -C $(LFTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LFTDIR) fclean
	rm -rf $(LMLXDIR)/build

re: clean all

.PHONY: all clean fclean re