# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    display.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpitot <mpitot@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/01 12:21:59 by mpitot            #+#    #+#              #
#    Updated: 2024/05/11 17:01:16 by mpitot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[1;31m
GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
MAGENTA	=	\033[1;35m
CYAN	=	\033[1;36m
WHITE	=	\033[1;37m
DEFAULT	=	\033[0m
UP		=	"\033[A"
CUT		=	"\033[K"

CHANGED	=	0
NUM_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

define separator
	@echo "$(WHITE)------------------------------------------------------------$(DEFAULT)"
endef

define print_progress
	@echo "$(YELLOW)Compiling $(WHITE)[$(BLUE)$(patsubst $(SRC_D)%,%,$1)$(WHITE)]...$(DEFAULT)\r"
endef

define update_progress
	$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS) + 1))))
	$(eval PROGRESS := $(shell echo $$((($(COMPILED_SRCS) * 100) / $(NUM_SRCS)))))
	@printf ${UP}${CUT}
	@if [ $(PROGRESS) -eq 100 ]; then \
		echo "$(WHITE)<$(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$(patsubst $(SRC_D)%,%,$1)$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
	else \
		if [ $(PROGRESS) -lt 10 ]; then \
			echo "$(WHITE)<  $(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$(patsubst $(SRC_D)%,%,$1)$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
		else \
			echo "$(WHITE)< $(GREEN)$(PROGRESS)%$(WHITE)> $(WHITE)[$(BLUE)$(patsubst $(SRC_D)%,%,$1)$(WHITE)] $(YELLOW)compiled.$(DEFAULT)\r"; \
		fi \
	fi
endef

define erase
	@printf ${UP}${CUT}
endef

define done_and_dusted
	@echo "$(WHITE)[$(CYAN)$1$(WHITE)] $(GREEN)compiled.$(DEFAULT)"
endef

.internal_separate1	:
	$(call separator)

.internal_separate2 :
	$(call separator)

.internal_separate3 :
	$(call separator)