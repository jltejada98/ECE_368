TARGET = pa5
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa5.c sorting.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) -q ./Inputs/1k.b 1ksorted.b
	$(VALGRIND)=./valgrind2.log ./$(TARGET) -m ./Inputs/1k.b 1ksorted.b
	$(VALGRIND)=./valgrind3.log ./$(TARGET) -q ./Inputs/100k.b 100ksorted.b
	$(VALGRIND)=./valgrind4.log ./$(TARGET) -m ./Inputs/100k.b 100ksorted.b

#Added rule to test all files.
testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10

test1: $(TARGET)
	time ./$(TARGET) -q ./Inputs/1k.b 1ksorted.b
	time ./$(TARGET) -m ./Inputs/1k.b 1ksorted.b

test2: $(TARGET)
	time ./$(TARGET) -q ./Inputs/10k.b 10ksorted.b
	time ./$(TARGET) -m ./Inputs/10k.b 10ksorted.b

test3: $(TARGET)
	time ./$(TARGET) -q ./Inputs/100k.b 100ksorted.b
	time ./$(TARGET) -m ./Inputs/100k.b 100ksorted.b

test4: $(TARGET)
	time ./$(TARGET) -q ./Inputs/1M.b 1Msorted.b
	time ./$(TARGET) -m ./Inputs/1M.b 1Msorted.b

test5: $(TARGET)
	time ./$(TARGET) -q ./Inputs/10M.b 10Msorted.b
	time ./$(TARGET) -m ./Inputs/10M.b 10Msorted.b

test6: $(TARGET)
	time ./$(TARGET) -q ./Inputs/20M.b 20Msorted.b
	time ./$(TARGET) -m ./Inputs/20M.b 20Msorted.b

test7: $(TARGET)
	time ./$(TARGET) -q ./Inputs/32M.b 32Msorted.b
	time ./$(TARGET) -m ./Inputs/32M.b 32Msorted.b

test8: $(TARGET)
	time ./$(TARGET) -q ./Inputs/ascending_1M.b ascending_1Msorted.b
	time ./$(TARGET) -m ./Inputs/ascending_1M.b ascending_1Msorted.b

test9: $(TARGET)
	time ./$(TARGET) -q ./Inputs/descending_1M.b descending_1Msorted.b
	time ./$(TARGET) -m ./Inputs/descending_1M.b descending_1Msorted.b

test10: $(TARGET)
	time ./$(TARGET) -q ./Inputs/half_1M.b half_1Msorted.b
	time ./$(TARGET) -m ./Inputs/half_1M.b half_1Msorted.b

clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log *.b
