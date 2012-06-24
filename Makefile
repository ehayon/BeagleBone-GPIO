SRC = gpio.c
OBJ = $(SRC:.c=.o)
OBJLIBS	= 
NAME = libbeaglebone.a
TMS = main.c
TMO = $(TMS:.c=.o)
TMN = beaglebone
LIBS = 
LIBPATH = .
RM = rm -f

all: $(OBJ)
	ar -rc $(NAME) $(OBJ)
	ranlib $(NAME)

test: $(NAME) $(OBJLIBS) $(TMO)
	cc -L$(LIBPATH) $(TMO) $(LIBS) -o $(TMN)
			
clean:
	-$(RM) *.o
	-$(RM) *~
	-$(RM) \#*
	-$(RM) *.core

fclean: clean
	-$(RM) $(NAME)
	-$(RM) $(TMN)
	-$(RM) $(OBJLIBS)

libminheap.a: force_look
	cd minheap; $(MAKE) all $(MFLAGS)
			
libqueue.a: force_look
	cd queue; $(MAKE) all $(MFLAGS)	
			
re: fclean all

$(NAME): all

ftest: $(OBJLIBS) test

force_look :
	true
