TARGET	=	render_test
DEPS	=	$(TARGET).deps
CARGS	=	-Wall -g
CC		= 	clang
OBJS	=	render.o \
			hash.o \
			alloc.o \
			main.o

%.o:%.c
	$(CC) $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS) $(DEPS)
	$(CC) $(CARGS) -o $(TARGET) $(OBJS)

$(DEPS): $(OBJS:.o=.c)
	$(CC) -MM $^ > $(DEPS)

include $(DEPS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) test1.out


