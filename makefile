OBJS1	=	server.o net.o
TARGET1	=	server
CFLAGS	=	-c -DNDEBUG

.c.o:
	gcc $(CFLAGS) $<

all: $(TARGET1)

$(TARGET1):	$(OBJS1)
	gcc -o $(TARGET1) $(OBJS1) -lm -lSDL2

clean:
	rm *.o $(TARGET1)

server.o: server.c server.h constant.h net.h
net.o: net.c net.h constant.h