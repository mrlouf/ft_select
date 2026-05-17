NAME			= ft_select

DEL_LINE =		\033[2K
ITALIC =		\033[3m
BOLD =			\033[1m
DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m
MAGENTA =		\033[0;95m
CYAN =			\033[0;96m
WHITE =			\033[0;97m
BLACK =			\033[0;99m
ORANGE =		\033[38;5;209m
BROWN =			\033[38;2;184;143;29m
DARK_GRAY =		\033[38;5;234m
MID_GRAY =		\033[38;5;245m
DARK_GREEN =	\033[38;2;75;179;82m
DARK_YELLOW =	\033[38;5;143m
GREEN := 		\033[0;92m

SRC				= 	main.c 	\
					signal.c 	\
					keys.c 		\
					moves.c 	\
					render.c 	\
					conf.c 		\
					buffer.c 	\
					termcap.c	\

INCLUDE			=	./inc/ft_select.h

LIBFT			=	./libft/libft.a

SRCDIR			=	src
SRCS			=	$(addprefix $(SRCDIR)/, $(SRC))

OBJDIR			=	.obj
OBJS			=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR			=	.dep
DEPS			=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))

LOGFILE			=	./ft_select.log

CC				= cc
RM				= rm -fr
CFLAGS			= -g -fsanitize=address # -Wall -Wextra -Werror -g

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MT $@ -MMD -MP -c $< -o $@
	@mkdir -p $(DEPDIR)
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/
	@echo "${BLUE} ◎ $(BROWN)Compiling   ${MAGENTA}→   $(CYAN)$< $(DEF_COLOR)"

all:	make_libft ${NAME}
	@rm -f $(LOGFILE)

make_libft:
	@make -C libft

-include $(DEPS)

${NAME}: ${OBJS} Makefile
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -ltinfo -o $(NAME)
	@echo "$(GREEN)Created ${NAME} ✓$(DEF_COLOR)\n"

clean:
	@${RM} .dep .obj
	@make -C libft clean
	@echo "\n${BLUE} ◎ $(RED)All objects cleaned successfully ${BLUE}◎$(DEF_COLOR)\n"

fclean:
	@${RM} .dep .obj ${NAME} ${LOGFILE}
	@make -C libft fclean
	@echo "\n${BLUE} ◎ $(RED)All objects and executable cleaned successfully${BLUE} ◎$(DEF_COLOR)\n"

re: fclean all 

.PHONY: all clean fclean re