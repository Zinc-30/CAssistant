OBJS = main.c
CC = clang
EXEC = ca
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) 
#	rm *.o
