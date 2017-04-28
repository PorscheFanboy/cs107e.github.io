CPPFLAGS = 
CFLAGS = -Wall -std=c99 $(CPPFLAGS)
LDFLAGS = 

NAME = main
OBJECTS = tricky.o
 
$(NAME).exe: $(NAME).o $(OBJECTS)
	cc -o $@ $^

clean:
	rm -f *.exe *.o

# Targets that aren't filename of build product should be declared "phony" 
.PHONY: all clean

