TARGET = pa1
CFLAGS = -std=c99 -Wall -Wshadow -Wvla -pedantic -O3
GCC = gcc $(CFLAGS)

SRCS = huffman_main.c huffman.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file


$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET)
	
#Added rule to test all files.
testall: test1 test2 test3 test4

test1: $(TARGET)
	./$(TARGET) original/gophers empty.count empty.tree empty.code empty.hbt
	diff empty.count count/gophers.count

test2: $(TARGET)
	./$(TARGET) original/lorum empty.count empty.tree empty.code empty.hbt
	diff empty.count count/lorum.count

test3: $(TARGET)
	./$(TARGET) original/stone empty.count empty.tree empty.code empty.hbt
	diff empty.count count/stone.count

test4: $(TARGET)
	./$(TARGET) original/woods empty.count empty.tree empty.code empty.hbt
	diff empty.count count/woods.count

clean:
	rm -f $(OBJS) $(TARGET)
