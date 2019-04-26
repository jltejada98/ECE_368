TARGET = pa6
GDBFLAGS = -g
CFLAGS = -O3 -std=c99 -Wall -Wshadow -Wvla -pedantic $(GDBFLAGS)
GCC = gcc $(CFLAGS)

SRCS = pa6.c seqpair.c

OBJS = $(SRCS:%.c=%.o)
VALGRIND = valgrind --tool=memcheck --verbose --log-file

$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

.c.o:
	$(GCC) $(TESTFLAGS) -c $*.c

testmemory: $(TARGET)
	$(VALGRIND)=./valgrind1.log ./$(TARGET) ./Input/r8.sp r8.pck
	$(VALGRIND)=./valgrind2.log ./$(TARGET) ./Input/r100.sp r100.pck
	$(VALGRIND)=./valgrind3.log ./$(TARGET) ./Input/r100h.sp r100h.pck
	$(VALGRIND)=./valgrind4.log ./$(TARGET) ./Input/r100v.sp r100v.pck
	$(VALGRIND)=./valgrind5.log ./$(TARGET) ./Input/r1K.sp r1K.pck
	$(VALGRIND)=./valgrind6.log ./$(TARGET) ./Input/r2K.sp r2K.pck

#Added rule to test all files.
testall: test0 test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12

test0: $(TARGET)
	time ./$(TARGET) ./Input/r8_original.sp r8_original.pck
	diff r8_original.pck Expected/r8.pck


test1: $(TARGET)
	time ./$(TARGET) ./Input/r1.sp r1.pck
	diff r1.pck Expected/r1.pck

test2: $(TARGET)
	time ./$(TARGET) ./Input/r5.sp r5.pck
	diff r5.pck Expected/r5.pck

test3: $(TARGET)
	time ./$(TARGET) ./Input/r20.sp r20.pck
	diff r20.pck Expected/r20.pck

test4: $(TARGET)
	time ./$(TARGET) ./Input/r50.sp r50.pck
	diff r50.pck Expected/r50.pck

test5: $(TARGET)
	time ./$(TARGET) ./Input/r200.sp r200.pck
	diff r200.pck Expected/r200.pck

test6: $(TARGET)
	time ./$(TARGET) ./Input/r2000.sp r2000.pck
	diff r2000.pck Expected/r2000.pck

test7: $(TARGET)
	time ./$(TARGET) ./Input/r5000.sp r5000.pck
	diff r5000.pck Expected/r5000.pck

test8: $(TARGET)
	time ./$(TARGET) ./Input/r8000.sp r8000.pck
	diff r8000.pck Expected/r8000.pck

test9: $(TARGET)
	time ./$(TARGET) ./Input/r10000.sp r10000.pck
	diff r10000.pck Expected/r10000.pck

test10: $(TARGET)
	time ./$(TARGET) ./Input/r15000.sp r15000.pck
	diff r15000.pck Expected/r15000.pck

test11: $(TARGET)
	time ./$(TARGET) ./Input/r50000.sp r50000.pck
	diff r50000.pck Expected/r50000.pck

test12: $(TARGET)
	time ./$(TARGET) ./Input/r100000.sp r100000.pck
	diff r100000.pck Expected/r100000.pck

clean:
	rm -f $(OBJS) $(TARGET) valgrind?.log *.b *.pck
