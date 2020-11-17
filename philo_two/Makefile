NAME = philo_two
HEADER = philo.h
CFLAGS = -Wall -Wextra -Werror

SRC = ./srcs/philo_two.c ./srcs/init_table.c ./srcs/init_philo.c\
		 ./srcs/utils.c ./srcs/simulation.c

OBJ = $(patsubst %.c,%.o,$(SRC))



all: $(NAME)
$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

norm: 
	norminette */*.c */*.h

.PHONY: all clean fclean re bonus norm