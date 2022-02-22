NAME = philo


SRCS = philosophers.c utils.c init.c \
	philo_utils/ph_atoi.c\
	philo_utils/ph_isdigit.c\
	philo_utils/ph_strlen.c\

FLAGS = -Wall -Wextra -Werror

# SANITIZE = -fsanitize=address -g

all: $(NAME) 

$(NAME): $(SRCS)
	@gcc $(FLAGS) $(SRCS) -lpthread -o $(NAME)

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all