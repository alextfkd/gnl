
NAME = libftgnl.a
SRCS = ./get_next_line.c ./get_next_line_utils.c
OBJS = $(SRCS:./%.c=./%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
AR = ar
ARFLAGS = rcs

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all# bonus

.PHONY: all clean fclean re bonus
