CPP=g++ 
INCLUDE=-I./include -I/usr/include/nauty
LIBS=
CPPFLAGS=-g -O3 -w $(INCLUDE) $(LIBS)
PROGRAM=nautyTest

SRC=src/nautyCaller.cpp\
    src/testnautyCaller.cpp

NAUTY = nautylibrary/nauty.o\
        nautylibrary/naugraph.o\
        nautylibrary/nautil.o

OBJ=$(SRC:.cpp=.o)

all : $(PROGRAM)

%.o: src/%.cpp include/%.h
	$(CPP) $(CPPFLAGS) -c $< -o $@

nautylibrary/%.o: nautylibrary/%.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ) $(NAUTY)
	$(CPP) $(CPPFLAGS) -o $@ $(OBJ) $(NAUTY)

clean:
	@echo "Removing objects..."
	rm -f $(PROGRAM) *.log src/*.o src/*~ include/*~ *~ core
	rm -f nautylibrary/*.o 

install: $(PROGRAM)
	cp $(PROGRAM) ../bin

ar:
	make clean
	tar -czvf ../$(PROGRAM)"(`date`)".tar.gz *