DIR = src/
SRC = gpio.c
OBJ = $(DIR)$(SRC:.c=.o)
NAME = libgpiommap.a
TMS = main.c
TMO = $(TMS:.c=.o)
TMN = gpiommap 
LIBS = -lgpiommap
LIBPATH = .
RM = rm -f

all: $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

test: $(NAME) $(TMO)
	cc -L$(LIBPATH) $(TMO) $(LIBS) -o $(TMN)

clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)
	-$(RM) $(TMN)

re: fclean all

$(NAME): all

ftest: fclean test
