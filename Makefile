TARGET	=	render_test
DEPS	=	$(TARGET).deps
CARGS	=	-Wall -g
CC		= 	clang
OBJS	=	template.o \
			render.o \
			hash.o \
			alloc.o \
			main.o

%.o:%.c
	$(CC) $(CARGS) -c -o $@ $<

$(TARGET): $(OBJS) $(DEPS)
	$(CC) $(CARGS) -o $(TARGET) $(OBJS)

template.c template.h: template.l
	flex template.l

$(DEPS): $(OBJS:.o=.c)
	$(CC) -MM $^ > $(DEPS)

include $(DEPS)

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS) template.c template.h test1.out


