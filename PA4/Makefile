TARGET = pa4
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa4.c build.c utility.c evaluate.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) -b Inputs/ops0.b tree0.b
	$(VALGRIND)=./valgrind2.log ./$(TARGET) -b Inputs/ops1.b tree1.b
	$(VALGRIND)=./valgrind3.log ./$(TARGET) -b Inputs/ops2.b tree2.b
	$(VALGRIND)=./valgrind4.log ./$(TARGET) -b Inputs/ops3.b tree3.b
	$(VALGRIND)=./valgrind5.log ./$(TARGET) -e Inputs/invalidtree0.b
	$(VALGRIND)=./valgrind6.log ./$(TARGET) -e Inputs/invalidtree1.b
	$(VALGRIND)=./valgrind7.log ./$(TARGET) -e Inputs/invalidtree2.b

#Added rule to test all files.
testall: test1 test2 test3 test4 test5 test6 test7

test1: $(TARGET)
	./$(TARGET) -b Inputs/ops0.b tree0.b
	diff tree0.b Expected_Output/tree0.b

test2: $(TARGET)
	./$(TARGET) -b Inputs/ops1.b tree1.b
	diff tree1.b Expected_Output/tree1.b

test3: $(TARGET)
	./$(TARGET) -b Inputs/ops2.b tree2.b
	diff tree2.b Expected_Output/tree2.b

test4: $(TARGET)
	./$(TARGET) -b Inputs/ops3.b tree3.b
	diff tree3.b Expected_Output/tree3.b

test5: $(TARGET)
	./$(TARGET) -e Inputs/invalidtree0.b

test6: $(TARGET)
	./$(TARGET) -e Inputs/invalidtree1.b

test7: $(TARGET)
	./$(TARGET) -e Inputs/invalidtree2.b

clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log  *.b
