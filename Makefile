# --- Compiler -------------------- #

CC = cc

# --- Compiler Flags -------------- #

CFLAGS = -g -Wall -Wextra -Werror

# --- NAME ---------------------- #

NAME = compress

NODIR = --no-print-directory

# --- PUSH SWAP SOURCES ------------ #
VPATH = src:hashtable
SRCS = $(wildcard src/*.c) $(wildcard hashtable/*.c)

OBJS = $(addprefix obj/,$(notdir $(SRCS:.c=.o)))

RM = rm -f

all: $(NAME)

obj/%.o: %.c | obj
	$(CC) -c $(CFLAGS) $< -o $@

obj:
	mkdir -p obj

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	@rm -rf obj

fclean:	clean
	@$(RM) $(NAME)

re:
	@make fclean $(NODIR)
	@make $(NODIR)

r:
	@make $(NODIR)
	@echo "------"
	@./compress text.txt new.txt

.PHONY: all clean fclean re r
