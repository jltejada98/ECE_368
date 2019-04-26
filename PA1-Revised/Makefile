TARGET = pa1
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa1.c huffman.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) original/gophers gophers.count gophers.tree gophers.code gophers.hbt
	$(VALGRIND)=./valgrind2.log ./$(TARGET) original/lorum lorum.count lorum.tree lorum.code lorum.hbt
	$(VALGRIND)=./valgrind3.log ./$(TARGET) original/stone stone.count stone.tree stone.code stone.hbt
	$(VALGRIND)=./valgrind4.log ./$(TARGET) original/woods woods.count woods.tree woods.code woods.hbt
	$(VALGRIND)=./valgrind5.log ./$(TARGET) original/empty empty.count empty.tree empty.code empty.hbt

#Added rule to test all files.
testall: test1 test2 test3 test4 test5 test6

test1: $(TARGET)
	./$(TARGET) original/gophers gophers.count gophers.tree gophers.code gophers.hbt
	diff gophers.count count/gophers.count
	diff gophers.code code/gophers.code
	diff gophers.tree tree/gophers.tree

test2: $(TARGET)
	./$(TARGET) original/lorum lorum.count lorum.tree lorum.code lorum.hbt
	diff lorum.count count/lorum.count
	diff lorum.code code/lorum.code
	diff lorum.tree tree/lorum.tree

test3: $(TARGET)
	./$(TARGET) original/stone stone.count stone.tree stone.code stone.hbt
	diff stone.count count/stone.count
	diff stone.code code/stone.code
	diff stone.tree tree/stone.tree

test4: $(TARGET)
	./$(TARGET) original/woods woods.count woods.tree woods.code woods.hbt
	diff woods.count count/woods.count
	diff woods.code code/woods.code
	diff woods.tree tree/woods.tree

test5: $(TARGET)
	./$(TARGET) original/binary1 binary1.count binary1.tree binary1.code binary1.hbt
	diff binary1.count count/binary1.count
	diff binary1.code code/binary1.code
	diff binary1.tree tree/binary1.tree


test6: $(TARGET)
	./$(TARGET) original/empty empty.count empty.tree empty.code empty.hbt
	diff empty.count count/empty.count
	diff empty.code code/empty.code
	diff empty.tree tree/empty.tree


clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log  *.b *.code *.count *.tree
