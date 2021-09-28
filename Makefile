.PHONY = all clean

CC := g++

LINKERFLAG = -lm
PYFLAGl =`pkg-config --cflags python3`
PYFLAGc =`pkg-config --cflags python3`

SRCS := generate.cc plot.cc
BINS := $(SRCS:%.cc=%)
OBJS := $(SRCS:%.cc=%.o)

all: ${BINS} ${OBJS}

%: %.o
	@echo "Checking..."
	${CC} ${PYFLAGl} ${LINKERFLAG} $< -o $@ -lpython3.9

%.o: %.cc
	@echo "Creating object..."
	${CC} -I/usr/lib/python3.9/site-packages/numpy/core/include/ ${PYFLAGc} -c $< -o $@ 

clean:
	@echo "Cleaning up..."
	@rm -rvf *.o ${BINS}
