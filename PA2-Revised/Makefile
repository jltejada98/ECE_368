TARGET = pa2
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa2.c sequence.c shell_array.c shell_list.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) -a ./Inputs/15.b 15sa.b
	$(VALGRIND)=./valgrind2.log ./$(TARGET) -l ./Inputs/15.b 15sa.b
	$(VALGRIND)=./valgrind3.log ./$(TARGET) -a ./Inputs/1000.b 1000sa.b
	$(VALGRIND)=./valgrind4.log ./$(TARGET) -l ./Inputs/1000.b 1000sa.b
	
#Added rule to test all files.
testall: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10


test1: $(TARGET)
	./$(TARGET) -a ./Inputs/15.b 15sa.b
	diff 15sa.b ./Expected_Output/15sa.b

test2: $(TARGET)
	./$(TARGET) -l ./Inputs/15.b 15sl.b
	diff 15sl.b ./Expected_Output/15sl.b

test3: $(TARGET)
	./$(TARGET) -a ./Inputs/1000.b 1000sa.b
	diff 1000sa.b ./Expected_Output/1000sa.b

test4: $(TARGET)
	./$(TARGET) -l ./Inputs/1000.b 1000sl.b
	diff 1000sl.b ./Expected_Output/1000sl.b

test5: $(TARGET)
	./$(TARGET) -a ./Inputs/10000.b 10000sa.b

test6: $(TARGET)
	./$(TARGET) -l ./Inputs/10000.b 10000sl.b

test7: $(TARGET)
	./$(TARGET) -a ./Inputs/100000.b 100000sa.b

test8: $(TARGET)
	./$(TARGET) -l ./Inputs/100000.b 100000sl.b

test9: $(TARGET)
	./$(TARGET) -a ./Inputs/1000000.b 1000000sa.b

test10: $(TARGET)
	./$(TARGET) -l ./Inputs/1000000.b 1000000sl.b

clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log  *.b
