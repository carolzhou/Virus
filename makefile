CC = g++
CFLAGS = -g -O0

PROGRAM = Qspp_main.exe

CSRC	=	TRandomMersenne.cpp \
		Position.cpp  \
		Fitness.cpp \
		Genotype.cpp \
		Population.cpp \
		Cloud.cpp \
		Qspp_main.cpp

OBJ	=	TRandomMersenne.o \
		Position.o  \
		Fitness.o \
		Genotype.o \
		Population.o \
		Cloud.o \
		Qspp_main.o

all: $(PROGRAM)

$(PROGRAM):	$(OBJ)
	$(CC) $(OBJ) -o $@
	@echo "done"

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean: 
	rm -f *.o *.exe
