NAME	=	cub3d

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -O3
MLXFLAGS=	-ldl -lglfw -pthread -lm

LMLXDIR	=	./MLX42
LIBMLX	=	$(LMLXDIR)/build/libmlx42.a 

LFTDIR	=	./libft
LIBFT	=	$(LFTDIR)/libft.a

SRCDIR	=	./src
SRC		=	$(SRCDIR)/main.c \
			$(SRCDIR)/draw_utils.c \
			$(SRCDIR)/init.c \
			$(SRCDIR)/map_read.c \
			$(SRCDIR)/raycast.c \
			$(SRCDIR)/rotate_vector.c \
			$(SRCDIR)/user_inputs_keyscroll.c \
			$(SRCDIR)/user_inputs.c \
			$(SRCDIR)/utils_calc.c \
			$(SRCDIR)/utils_free.c \
			$(SRCDIR)/utils_test.c
# $(SRCDIR)/draw.c \

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
