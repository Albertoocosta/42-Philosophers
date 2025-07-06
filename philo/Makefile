NAME = philo
CC = cc
FLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init.c actions.c routine.c routine2.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean: 
	@rm -rf *.o

fclean: clean
	@rm $(NAME)
	@echo ALL CLEAR

re: fclean all