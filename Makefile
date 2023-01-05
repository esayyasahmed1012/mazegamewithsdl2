CC = gcc

SRC = *.c

OBJ = $(SRC:.c=.o)

NAME = maze
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pedantic

LFLAGS = -lSDL2 -lSDL2_image -lm

all: $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LFLAGS) -o $(NAME)
clean:
	$(RM) *~ $(NAME)
oclean:
	$(RM) $(OBJ)
fclean: clean oclean
re: oclean all
