NAME = pipex

COMMON_SCRS = ft_split_add_slush.c\
		utils.c\
		fork_and_child.c\
		parents.c\
		find_path.c\
		execve.c\
		initializer.c\
		free.c\
		ft_split_severals.c\
		
SRCS = pipex.c\

BONUS_SRCS = pipex_bonus.c\
		read_line.c\
		here_doc.c\
		
INCLUDE = -I./libft

LIBFT_DIR := ./libft

LIBFT = $(LIBFT_DIR)/libft.a

FLAGS = -Wall -Wextra -Werror -fsanitize=address -g

OBJS = $(SRCS:.c=.o)

COMMON_OBJS = $(COMMON_SCRS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all : .delete .mandatory

.delete : 
	@touch .delete
	@rm -f .timestaps .delete_bo

.mandatory: $(LIBFT) $(COMMON_OBJS) $(OBJS)
	@touch .mandatory
	@cp $(LIBFT) $(NAME).a
	@ar -rcs $(NAME).a $(OBJS) $(COMMON_OBJS)
	@gcc $(FLAGS) -o $(NAME) $(NAME).a
	@echo "\n$(Yellow)-----PIPEX HAS BEEN CREATED-----\n$(Ending)"

$(LIBFT):
	@echo "\n$(Blue)MAKING LIBFT$(Ending)\n"
	@$(MAKE) -C libft
	@echo "\n$(Blue)MAKING NOW >>> .....$(Ending)\n"

$(COMMON_OBJS): %.o: %.c
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(Green).$(Ending)"

$(OBJS): %.o: %.c
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(Green).$(Ending)"

bonus : .delete_bo .timestaps

.delete_bo : 
	@touch .delete_bo
	@rm -f .mandatory .delete

.timestaps :$(LIBFT) $(COMMON_OBJS) $(BONUS_OBJS)
	@touch .timestaps
	@cp $(LIBFT) $(NAME).a
	@ar -rcs $(NAME).a $(BONUS_OBJS) $(COMMON_OBJS)
	@gcc $(FLAGS) -o $(NAME) $(NAME).a
	@echo "\n$(Yellow)-----PIPEX BONUS HAS BEEN CREATED-----$(Ending)\n"

$(BONUS_OBJS): %.o: %.c 
	@gcc $(FLAGS) $(INCLUDES) -o $@ -c $<
	@echo "$(Green).$(Ending)"

check_bonus:
		@if [ -f .timestaps ]; then \
			rm -f .timestaps .delete_bo; \
		fi

check_mandatory:	
		@if [ -f .mandatory ]; then \
			rm -f .mandatory .delete; \
		fi

clean : check_bonus check_mandatory
		@$(MAKE) -C libft/ clean
		@rm -rf $(OBJS) $(BONUS_OBJS) $(COMMON_OBJS)

fclean: clean
		@$(MAKE) -C libft/ fclean
		@rm -rf $(NAME).a $(NAME)
		@echo "\n$(Magenta)-----FCLEANED-----$(Ending)\n"
re: fclean all

re_bo : fclean bonus

.PHONY: all fclean clean re bonus check

Red = \033[0;31m
Green = \033[0;32m
Yellow = \033[0;33m
Blue = \033[0;34m
Magenta = \033[0;35m
Cyan = \033[0;36m
White = \033[0;37m
Ending = \033[0m