NAME = pipex

SRCS = pipex.c\
		ft_split_add_slush.c\
#find_path.c\
#struct_malloc.c\

INCLUDE = -I./Libft

LIBFT_DIR := ./Libft

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cp $(LIBFT) $(NAME).a
	ar -rcs $(NAME).a $(OBJS) 
	gcc $(FLAGS) -o $(NAME) $(NAME).a 

$(LIBFT):
	$(MAKE) -C Libft
	
%.o : %.c
	gcc $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
		$(MAKE) -C Libft/ clean
		rm -rf $(OBJS)

fclean: clean
		$(MAKE) -C Libft/ fclean
		rm -rf $(NAME).a

re: fclean all

.PHONY: all fclean clean re
