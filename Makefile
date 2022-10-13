CC = gcc
CFLAGS = -Wall -Wextra -Werror
SILHANG = philo
NAME = lphilo.a
FILE = philo.c \
		util.c \
		routine.c

OBJECTS = $(FILE:%.c=%.o)

all : $(SILHANG)

$(OBJECTS) : $(FILE)
	$(CC) $(CFLAGS) -c $(FILE)

$(NAME) : $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(SILHANG) : $(NAME)
	gcc $(CFLAGS) -o $(SILHANG) $(FILE)

clean :
	rm -rf $(OBJECTS)

fclean : clean
	rm -rf $(SILHANG) $(NAME)

re : fclean all