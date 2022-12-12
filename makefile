OBJS1	=	server.o net.o
OBJS2	=	client_main.o client_net.o client_net_command.o
TARGET1	=	server
TARGET2	=	client
CFLAGS	=	-c -DNDEBUG

.c.o:
	gcc $(CFLAGS) $<

all: $(TARGET1) $(TARGET2)

$(TARGET1):	$(OBJS1)
	gcc -o $(TARGET1) $(OBJS1) -lm -lSDL2
$(TARGET2):	$(OBJS2)
	gcc -o $(TARGET2) $(OBJS2) -lm -lSDL2 


clean:
	rm *.o $(TARGET1)

server.o: server.c server.h net.h
net.o: net.c net.h
client_main.o: client_main.c client_net.h
client_net.o: client_net.c client_net.h
client_net_command.o: client_net_command.c client_net.h