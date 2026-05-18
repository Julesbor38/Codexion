NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCDIR = src
OBJDIR = objs
DEPDIR = .deps
INCDIR = includes

SRCS = main.c parsing.c init.c threads.c utils.c routines.c monitor.c scheduler.c queue_scheduler.c utils_scheduler.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCLUDES = -I$(INCDIR)

DEPFLAGS = -MMD -MP -MF $(DEPDIR)/$*.d

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@mkdir -p $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) $(INCLUDES) -c $< -o $@

-include $(addprefix $(DEPDIR)/, $(SRCS:.c=.d))

clean: 
	rm -rf $(DEPDIR)
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
