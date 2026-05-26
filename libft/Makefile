# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		= 	libft.a

# -=-=-=-=-    COLOURS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #


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

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c 	\
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c 	\
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c\
			ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c 		\
			ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
			ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_printf.c ft_printf_conv.c ft_printf_utils.c ft_lstnew.c 		\
			ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c 	\
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c			\
			get_next_line.c ft_atoi_base.c cucufu.c free_array.c			\
			print_array.c ft_iscntrl.c ft_realloc.c

SRCDIR		=	src
SRCS		=	$(addprefix $(SRCDIR)/, $(SRC))
			
OBJDIR		=	.obj
OBJS		=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR		=	.dep
DEPS		=	$(addprefix $(DEPDIR)/, $(SRC:.c=.d))

HEADER		=	inc/libft.h inc/ft_printf.h

MAKE		=	Makefile
			
# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./
RM			= rm -fr

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(SRCS) $(MAKE)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)Created ${NAME} ✓$(DEF_COLOR)\n"
	
$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) $(MAKE)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -MT $@ -MMD -MP -c $< -o $@
	@mkdir -p $(DEPDIR)
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/
	
-include $(DEPS)

clean:
	@${RM} .dep .obj

fclean: clean
	@${RM} .dep .obj ${NAME}

re: fclean all

.PHONY:  all clean fclean re
