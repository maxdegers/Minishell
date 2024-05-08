# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbrousse <mbrousse@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/05/08 15:48:13 by mbrousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main/main.c					\
			main/main_loop.c			\
			main/signals.c				\
			main/satanast.c				\
			error/error.c				\
			parsing/parsing_env.c		\
			parsing/parsing_line.c		\
			parsing/utils.c				\
			parsing/set_block.c			\
			parsing/parsing_redir.c		\
			parsing/parsing_cote.c		\
			parsing/parsing_expand.c	\
			parsing/parsing_expand_utils.c	\
			parsing/ft_split_bis.c 		\
			parsing/parsing_word.c		\
			parsing/expand_here_doc.c	\
			utils/t_env.c				\
			utils/t_redir.c				\
			utils/t_env_utils.c			\
			utils/t_token_utils.c		\
			utils/t_token.c				\
			utils/t_block.c				\
			execution/exec.c			\
			execution/ft_cd.c			\
			execution/ft_echo.c			\
			execution/ft_execve.c		\
			execution/ft_exit.c			\
			execution/ft_export.c		\
			execution/ft_putenv.c		\
			execution/ft_pwd.c			\
			execution/ft_unset.c		\
			execution/redir.c
