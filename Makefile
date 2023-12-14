NAME = snake

CC = gcc

CFLAGS = -Wall -Werror -Wextra

INCLUDE = includes/

LINK = lib/

SRCS = srcs/main.c \
	  srcs/apple.c \
	  srcs/render.c \
	  srcs/snake.c \
	  srcs/texture.c

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -I$(INCLUDE) -L$(LINK) -o $(NAME) $(SRCS) -lmingw32 -lSDL2main -lSDL2 -g3

clean:
	rm $(NAME)