MAIN_OBJ = main.o
SOURCE_OBJ = $(MAIN_OBJ) \
						 diplomacy_functions.o \
						 order.o \
						 player.o \
						 region.o \
						 troop.o \
						 utilities.o 
HEADERS = diplomacy.function.h \
					global_variables.h \
					order.h \
					player.h \
					region.h \
					troop.h \
					utilities.h 

CXX = g++ 
CFLAGS = -c
LDFLAGS = -lm -O3 -Wall -finline-functions -funroll-loops 

diplomacy.x: $(SOURCE_OBJ)
	$(CXX) $(SOURCE_OBJ) $(LDFLAGS) -o $@
%.o: %.cc
	$(CXX) $(CFLAGS)  $< 
clean:
	@rm -f *.o
	@echo make clean: done
