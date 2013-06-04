

SOURCES = main.c char_oper.c indent.c parentheses.c del_comment.c file_io.c
OBJS = $(SOURCES: .c=.o)
OBJDIR = ./#obj/
CC = gcc

EXEC = ca

CFLAGS = -c -g -Wall
LDFLAGS = 

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OBJDIR)$(EXEC) 

.c.o:
	$(CC) $(CFLAGS) $< -o $(OBJDIR)$@

clean:
	@rm *.o $(EXEC)

run: all
	$(OBJDIR)$(EXEC)
