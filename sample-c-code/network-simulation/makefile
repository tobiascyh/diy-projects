CC = gcc
CFLAGS = -Wall -ansi
SRCDIR = src/
OBJDIR = obj/
TMPDIR = tmp/
BINDIR = bin/

all: simulator

simulator: compile link

compile: $(OBJDIR)n1.o $(OBJDIR)n2.o $(OBJDIR)n3.o $(OBJDIR)n4.o $(OBJDIR)n5.o $(OBJDIR)n6.o $(OBJDIR)n7.o

link: $(BINDIR)node1 $(BINDIR)node2 $(BINDIR)node3 $(BINDIR)node4 $(BINDIR)node5 $(BINDIR)node6 $(BINDIR)node7

$(OBJDIR)n1.o: $(SRCDIR)n1.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n1.c -o $(OBJDIR)n1.o
$(OBJDIR)n2.o: $(SRCDIR)n2.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n2.c -o $(OBJDIR)n2.o
$(OBJDIR)n3.o: $(SRCDIR)n3.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n3.c -o $(OBJDIR)n3.o
$(OBJDIR)n4.o: $(SRCDIR)n4.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n4.c -o $(OBJDIR)n4.o
$(OBJDIR)n5.o: $(SRCDIR)n5.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n5.c -o $(OBJDIR)n5.o
$(OBJDIR)n6.o: $(SRCDIR)n6.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n6.c -o $(OBJDIR)n6.o
$(OBJDIR)n7.o: $(SRCDIR)n7.c
	$(CC) $(CFLAGS) -c $(SRCDIR)n7.c -o $(OBJDIR)n7.o

$(BINDIR)node1: $(OBJDIR)n1.o
	$(CC) $(OBJDIR)n1.o -o $(BINDIR)node1
$(BINDIR)node2: $(OBJDIR)n2.o
	$(CC) $(OBJDIR)n2.o -o $(BINDIR)node2
$(BINDIR)node3: $(OBJDIR)n3.o
	$(CC) $(OBJDIR)n3.o -o $(BINDIR)node3
$(BINDIR)node4: $(OBJDIR)n4.o
	$(CC) $(OBJDIR)n4.o -o $(BINDIR)node4
$(BINDIR)node5: $(OBJDIR)n5.o
	$(CC) $(OBJDIR)n5.o -o $(BINDIR)node5
$(BINDIR)node6: $(OBJDIR)n6.o
	$(CC) $(OBJDIR)n6.o -o $(BINDIR)node6
$(BINDIR)node7: $(OBJDIR)n7.o
	$(CC) $(OBJDIR)n7.o -o $(BINDIR)node7

run:
	@./$(BINDIR)node7&
	@./$(BINDIR)node6&
	@./$(BINDIR)node5&
	@./$(BINDIR)node4&
	@./$(BINDIR)node3&
	@./$(BINDIR)node2&
	./$(BINDIR)node1

clean:
	rm -fr $(OBJDIR)*.o
	rm -fr $(TMPDIR)*
	rm -fr $(BINDIR)*
