TARGET	=	render_test
DEPS	=	$(TARGET).deps
CARGS	=	-Wall -g
CC		= 	clang
OBJS	=	scanner.o \
			hash.o \
			alloc.o \
			template.o \
			main.o

%.o:%.c
	$(CC) $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS) $(DEPS)
	$(CC) $(CARGS) -o $(TARGET) $(OBJS)

scanner.c scanner.h: scanner.l
	flex scanner.l

$(DEPS): $(OBJS:.o=.c)
	$(CC) -MM $^ > $(DEPS)

include $(DEPS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) scanner.c scanner.h test1.out


