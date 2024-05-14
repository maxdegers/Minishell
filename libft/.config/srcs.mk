# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 20:13:24 by mpitot            #+#    #+#              #
#    Updated: 2024/05/14 20:13:24 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=

DIR_TO		=	ft_to/
SRC_TO		=	ft_atoi.c	\
				ft_itoa.c
TO			=	$(addprefix $(DIR_TO), $(SRC_TO))

DIR_IS		=	ft_is/
SRC_IS		=	ft_isalnum.c	\
				ft_isalpha.c	\
				ft_isascii.c	\
				ft_isdigit.c	\
				ft_isprint.c
IS			=	$(addprefix $(DIR_IS), $(SRC_IS))

DIR_LST		=	ft_lst/
SRC_LST		=	ft_lstadd_back.c	\
				ft_lstadd_front.c	\
				ft_lstclear.c		\
				ft_lstdelone.c		\
				ft_lstiter.c		\
				ft_lstlast.c		\
				ft_lstmap.c			\
				ft_lstnew.c			\
				ft_lstsize.c
LST			=	$(addprefix $(DIR_LST), $(SRC_LST))

DIR_MEM		=	ft_mem/
SRC_MEM		=	ft_memchr.c		\
				ft_memcmp.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_memset.c		\
				ft_calloc.c		\
				ft_bzero.c
MEM			=	$(addprefix $(DIR_MEM), $(SRC_MEM))

DIR_STR		=	ft_is/
SRC_STR		=	ft_strchr.c		\
				ft_strcmp.c		\
				ft_strdup.c		\
				ft_striteri.c	\
				ft_strjoin.c	\
				ft_strlcat.c	\
				ft_strlcpy.c	\
				ft_strlen.c		\
				ft_strmapi.c	\
				ft_strncmp.c	\
				ft_strnstr.c	\
				ft_strrchr.c	\
				ft_strtrim.c	\
				ft_substr.c		\
				ft_split.c		\
STR			=	$(addprefix $(DIR_STR), $(SRC_STR))

