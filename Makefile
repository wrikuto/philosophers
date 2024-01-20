NAME	=	philo

SRCS	=	./src/main.c \
			./src/prepare_party.c\
			./src/ft_atoi.c \
			./src/philo.c \
			./src/dead_checker.c \
			./src/mutex.c \
			./src/time.c \
			./src/utils.c

CC		= cc
INC	=	../inc/
FLAGS	= -Wall -Wextra -Werror -fsanitize=thread -g -I$(INC)
# FLAGS	= -Wall -Wextra -Werror -I$(INC)
RM		= rm -rf

OBJS_PATH = ./objs/
SRCS_PATH = ./src/

SRCS_FILES =	main.c \
			prepare_party.c \
			ft_atoi.c \
			philo.c \
			dead_checker.c \
			mutex.c \
			time.c \
			utils.c

OBJS = $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

all:		$(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	mkdir -p $(OBJS_PATH)
	$(CC) $(FLAGS) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re

