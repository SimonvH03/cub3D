NAME = extractor

SRC = src/extractor.c

OBJ = $(SRC:.c=.o)

DIR = out

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3 $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

all: $(DIR) $(NAME)

$(DIR):
	mkdir -p $(DIR)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f $(DIR)/*.xpm

re: fclean clean all
