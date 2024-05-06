# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/06 16:12:25 by mpitot            #+#    #+#              #
#    Updated: 2024/05/06 13:58:57 by mbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include .config/srcs.mk
include .config/display.mk

OBJS	=	$(SRCS:%.c=${OBJ_D}%.o)

SRC_D	=	srcs/

OBJ_D	=	.objs/

HEAD	=	includes/

NAME	=	minishell

CC		=	cc

FLAGS	=	-I$(READLINE_DIR)/include -Wall -Wextra -Werror -g3

ifeq ($(shell uname), Darwin)
READLINE_DIR	=	$(shell brew --prefix readline)
endif
READLINE_LIB	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

all		:	libft ${NAME}

${OBJS}	:	${OBJ_D}%.o: ${SRC_D}%.c Makefile includes/minishell.h includes/colors.h
	@$(call print_progress,$<)
	@${CC} ${FLAGS} -I${HEAD} -c $< -o $@
	@$(call update_progress,$<)

${NAME}	:	${OBJ_D} ${OBJS} libft/libft.a
	@$(call print_progress,$(NAME))
	@${CC} ${FLAGS} ${OBJS} -L./libft -lft -I${HEAD} -o ${NAME} -lm ${READLINE_LIB}
	@$(eval CHANGED=1)
	@$(call erase)
	@$(call done_and_dusted,$(NAME))

${OBJ_D}:
	@mkdir -p ${OBJ_D}
	@mkdir -p ${OBJ_D}main
	@mkdir -p ${OBJ_D}error
	@mkdir -p ${OBJ_D}parsing
	@mkdir -p ${OBJ_D}utils
	@mkdir -p ${OBJ_D}execution

libft	:
	@make --no-print-directory -C ./libft
	@$(call separator)

clean	:
	@echo "Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft clean
	@$(call separator)
	@echo "Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"

fclean	:
	@echo "F***ing-Cleaning $(WHITE)[$(RED)libft$(WHITE)]...$(DEFAULT)"
	@make --no-print-directory -C ./libft fclean
	@$(call separator)
	@echo "F***ing-Cleaning $(WHITE)[$(RED)$(NAME)$(WHITE)]...$(DEFAULT)"
	@rm -rf ${OBJ_D}
	@echo "$(WHITE)[$(RED)$(OBJ_D)$(WHITE)] $(RED)deleted.$(DEFAULT)"
	@rm -f ${NAME}
	@echo "$(WHITE)[$(RED)$(NAME)$(WHITE)] $(RED)deleted.$(DEFAULT)"

leak: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re		:	fclean .internal_separate all

.PHONY	:	all clean fclean re libft leak

.NOTPARALLEL all:
	@if [ $(CHANGED) -eq 0 ]; then \
		echo "$(YELLOW)Nothing to be done for $(WHITE)[$(CYAN)$(NAME)$(WHITE)].$(DEFAULT)"; \
	fi

.internal_announce	:
	@echo "$(YELLOW)Compiling $(WHITE)[$(CYAN)minishell$(WHITE)]...$(DEFAULT)"

.internal_separate	:
	@echo "$(WHITE)------------------------------------------------------------$(DEFAULT)"
