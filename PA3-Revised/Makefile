TARGET = pa3
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa3.c node.c delay.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) Inputs/3.txt 3.pre 3.delay
	$(VALGRIND)=./valgrind2.log ./$(TARGET) Inputs/5.txt 5.pre 5.delay
	$(VALGRIND)=./valgrind3.log ./$(TARGET) Inputs/10.txt 10.pre 10.delay
	$(VALGRIND)=./valgrind4.log ./$(TARGET) Inputs/100.txt 100.pre 100.
	$(VALGRIND)=./valgrind5.log ./$(TARGET) Inputs/1000.txt 1000.pre 1000.delay
	
#Added rule to test all files.
testall: test1 test2 test3 test4 test5

test1: $(TARGET)
	./$(TARGET) Inputs/3.txt 3.pre 3.delay
	diff 3.pre Expected_Output/3.pre
	diff 3.delay Expected_Output/3.delay

test2: $(TARGET)
	./$(TARGET) Inputs/5.txt 5.pre 5.delay
	diff 5.pre Expected_Output/5.pre
	diff 5.delay Expected_Output/5.delay

test3: $(TARGET)
	./$(TARGET) Inputs/10.txt 10.pre 10.delay

test4: $(TARGET)
	./$(TARGET) Inputs/100.txt 100.pre 100.delay

test5: $(TARGET)
	./$(TARGET) Inputs/1000.txt 1000.pre 1000.delay

clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log  *.b *.pre *.delay
