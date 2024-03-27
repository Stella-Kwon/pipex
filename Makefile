NAME = pipex

SRCS = pipex.c\
		ft_split_add_slush.c\
		utils.c\
		read_line.c\
		here_doc.c\
		fork.c\
		find_path.c\

INCLUDE = -I./libft

LIBFT_DIR := ./libft

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@cp $(LIBFT) $(NAME).a
	@ar -rcs $(NAME).a $(OBJS) 
	@gcc $(FLAGS) -o $(NAME) $(NAME).a
	@echo "-----PIPEX HAS BEEN CREATED-----"

$(LIBFT):
	@$(MAKE) -C libft
	
%.o : %.c
	@gcc $(FLAGS) $(INCLUDE) -c $< -o $@
	@echo "."

clean:
		@$(MAKE) -C libft/ clean
		@rm -rf $(OBJS)

fclean: clean
		@$(MAKE) -C libft/ fclean
		@rm -rf $(NAME).a
		@echo "-----FCLEANED-----"
re: fclean all

.PHONY: all fclean clean re
