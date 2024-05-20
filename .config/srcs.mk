# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:18:49 by mpitot            #+#    #+#              #
#    Updated: 2024/05/20 01:36:13 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(MAIN)		\
			$(ERROR)	\
			$(PARSING)	\
			$(UTILS)	\
			$(EXEC)

DIR_MAIN	=	main/
SRC_MAIN	=	main.c			\
				main_loop.c		\
				signals.c		\
				ft_putheader.c
MAIN	=	$(addprefix $(DIR_MAIN), $(SRC_MAIN))

DIR_ERROR	=	error/
SRC_ERROR	=	error.c\
				error_utils.c
ERROR	=	$(addprefix $(DIR_ERROR), $(SRC_ERROR))

DIR_PARSING	=	parsing/
SRC_PARSING	=	parsing_env.c			\
				parsing_line.c			\
				utils.c					\
				set_block.c				\
				parsing_redir.c			\
				parsing_quote.c			\
				parsing_expand.c		\
				parsing_expand_utils.c	\
				ft_split_bis.c			\
				parsing_word.c			\
				expand_here_doc.c		\
				expand_here_doc_utils.c
PARSING	=	$(addprefix $(DIR_PARSING), $(SRC_PARSING))


DIR_UTILS	=	utils/
SRC_UTILS	=	t_env.c			\
				t_env_utils.c	\
				t_redir.c		\
				t_token.c		\
				t_token_utils.c	\
				t_block.c		\
				here_doc.c		\
				pipe.c
UTILS	=	$(addprefix $(DIR_UTILS), $(SRC_UTILS))

DIR_EXEC	=	execution/
SRC_EXEC	=	exec.c			\
				ft_cd.c				\
				ft_echo.c			\
				ft_execve.c			\
				ft_execve_utils.c	\
				ft_exit.c			\
				ft_export.c			\
				ft_export_utils.c	\
				ft_putenv.c			\
				ft_pwd.c			\
				ft_unset.c			\
				redir.c				\
				close_fds.c			\
				forking.c			\
				piping.c
EXEC	=	$(addprefix $(DIR_EXEC), $(SRC_EXEC))
